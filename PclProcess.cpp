// PclProcess.cpp : アプリケーションのエントリ ポイントを定義します。
//

//#include "stdafx.h"
#include <vector>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/console/parse.h>
////#include <iostream>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/cloud_viewer.h>
//下記ヘッダを読み込むとエラーになる
//#include <pcl/segmentation/min_cut_segmentation.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/project_inliers.h>
#include <random>

#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
//#include <boost/thread/thread.hpp>
#include <iostream>
#include <pcl/io/ply_io.h>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <Eigen/Dense>
#include <fstream>

using vecPCloudXYZ = std::vector<pcl::PointCloud<pcl::PointXYZ>>;

//計算条件の設定を格納する構造体
//関数 clusterで使用
struct SettingCluster
{
	//setLeafSizeで使用
	float LEAF_SIZE_X = 1.7f;
	float LEAF_SIZE_Y = 1.7f;
	float LEAF_SIZE_Z = 1.7f;

	//setMaxIterationsで使用
	int MAX_ITERATION = 1000;

	//setDistanceThresholdで使用
	float DISTANCE_THRESHOLD = 5;

	//setMinClusterSize,setMaxClusterSizeで使用
	int CLUSTER_MIN_SIZE = 3000;
	int CLUSTER_MAX_SIZE = 30000;

	//setClusterToleranceで使用
	float CLUSTER_TOLERANCE = 5;

	//ファイルの保存を有効にするか否か
	bool USE_SAVE_FILE = true;

	//ファイルの保存先
	std::string FILE_SAVE_PATH = "";

	//削除した平面の点群ファイル名
	std::string REMOVE_FILE_NAME = "cloud_remove";

	//検出したクラスター点群のファイル名
	std::string CLUSTER_FILE_NAME = "cluster";

	//保存ファイルにタイムスタンプを使用する
	bool USE_TIME_TO_FILE = true;

};

/// <summary>
/// 指定フォルダから指定拡張子ファイルリストを取得する
/// </summary>
/// <param name="path">指定フォルダへのパス（絶対パス/相対パス）</param>
/// <param name="ext">指定拡張子名 例：.txt ドットを不空</param>
/// <returns>条件がマッチしたファイルへのパスのリスト</returns>
std::vector<std::string> GetFiles(const std::string& path, const std::string& ext)
{
	//入力は指定フォルダへのパスと、探し出す拡張子
	//指定フォルダは、
	// [絶対値指定] c:\document\ 
	// [相対値指定] .\testFolder\
	//　上記両方の指定方法で、指定
	//拡張子
	// .txt or .TXT などの様に、ドットを含み、大文字小文字両方の場合がある
	// 戻り値は、条件にマッチしたファイルへのパスのリスト

	std::vector<std::string> tmpAns;

	return tmpAns;
}

/// <summary>
/// 点群のフィルタ処理（指定Z範囲以外の点群を除去する）
/// </summary>
/// <param name="clowd">入力および、出力の点群へのポインタ</param>
/// <param name="minZ">Z方向の最小値</param>
/// <param name="maxZ">Z方向の最大値</param>
/// <param name=""></param>
void FilterCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr clowd, float minZ, float maxZ)
{
	pcl::PassThrough<pcl::PointXYZ>pass;
	pass.setInputCloud(clowd);
	pass.setFilterFieldName("z");
	pass.setFilterLimits(minZ, maxZ);
}


/// <summary>
/// 点群をクラスタリングする
/// </summary>
/// <param name="clowd">入力する点群情報</param>
/// <param name="cSetting">クラスタリングする設定値</param>
/// <returns></returns>
vecPCloudXYZ GetClusters(pcl::PointCloud<pcl::PointXYZ>::Ptr clowd, SettingCluster cSetting)
{
	vecPCloudXYZ tmpAns;

	return tmpAns;
}

/// <summary>
/// 
/// </summary>
/// <param name="clowd"></param>
/// <returns></returns>
std::vector<float> GetPlane(pcl::PointCloud<pcl::PointXYZ>::Ptr clowd)
{
	//参考先
	//http://pointclouds.org/documentation/tutorials/planar_segmentation.php

	//戻り値
	//平面の中心
	//X,Y,Z,	並進成分[mm]
	//rx,ry,rz　回転成分[deg]
	//平面を四角形でフィッティングした時のL方向、W方向

	float x, y, z;
	float rx, ry, rz;
	float planeL, planeW, planeTheta;

	//平面を見つける処理を書く
	//xyx rx,ry,rz, planeL, planeW, planeThetaに代入


	//戻り値の作成
	std::vector<float> tmpAns{x,y,z,rx,ry,rz,planeL,planeW,planeTheta};

	return tmpAns;
}



int main()
{
	//指定フォルダ内のpcdファイルを検索する

	//検索したpcdファイル群を１個づつ処理する

	//処理内容は、
	//・指定範囲内の点群データを処理する(Zの範囲を指定)
	//・点群データから、クラスタリングを行う
	//・クラスタリングごとに、平面の検出を行う
	//・平面を四角形でフィッティングし、
	//長辺、短辺の長さ、中心位置、カメラ座標系に対する四角形の傾きを計算する
	//・結果を点群とともに、画面に描画する
	//・処理結果をテキストに書き出す
	//・・ファイル名：検出結果....

	//処理内容をフォルダ内のPCDファイルについて繰り返し処理する

	auto files = GetFiles("./", ".pcd");
	if(files.size() !=0)
	{
		for (auto fileName : files)
		{
			//pcdファイルを読み込む
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
			pcl::PCDReader reader;
			reader.read(fileName, *cloud);

			//フィルタ処理
			FilterCloud(cloud, 0, 30);

			//クラスタリング
			SettingCluster sc;
			auto clusters = GetClusters(cloud, sc);

			//結果の出力
			for (auto pointsClowd : clusters)
			{
				//平面を見つける
				pcl::PointCloud<pcl::PointXYZ>::Ptr pClowd(new pcl::PointCloud<pcl::PointXYZ>{ pointsClowd });
				auto plane = GetPlane(pClowd);

				std::stringstream ss;
				ss << "plane info  : \n" 
				   << " XYZ        : " << plane[0] << "," << plane[1] << "," << plane[2] << std::endl;
				ss << " RX RY RZ   : " << plane[3] << "," << plane[4] << "," << plane[5] << std::endl;
				ss << " Plane size : " << plane[6] << "," << plane[7] << "," << plane[8] << std::endl;

				//ファイル名と結果をまとめてファイルに出力

				
			}

			//結果を画面に出力
			//参考先
			//http://pointclouds.org/documentation/tutorials/pcl_visualizer.php

			//Enterを押して、次のファイルの処理に進む

		}

		std::cout << "End of Process" << std::endl;
	}

	std::cout << "Press Enter to Exit." << std::endl;
	getchar();

    return 0;
}

