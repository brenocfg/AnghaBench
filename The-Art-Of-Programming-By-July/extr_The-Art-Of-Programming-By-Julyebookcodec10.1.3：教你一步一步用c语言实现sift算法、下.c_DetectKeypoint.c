#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct KeypointSt {int dummy; } ;
struct TYPE_16__ {int row; int col; TYPE_3__* Octave; } ;
struct TYPE_15__ {int subsample; TYPE_4__* Octave; } ;
struct TYPE_14__ {int row; int col; int sy; int sx; int octave; int level; int /*<<< orphan*/  scale; struct TYPE_14__* next; } ;
struct TYPE_13__ {double levelsigmalength; int /*<<< orphan*/  absolute_sigma; } ;
struct TYPE_12__ {TYPE_2__* Level; } ;
struct TYPE_10__ {scalar_t__ fl; } ;
struct TYPE_11__ {int step; TYPE_1__ data; } ;
typedef  TYPE_5__* Keypoint ;
typedef  TYPE_6__ ImageOctaves ;

/* Variables and functions */
 scalar_t__ CONTRAST_THRESHOLD ; 
 int CURVATURE_THRESHOLD ; 
 TYPE_9__* DOGoctaves ; 
 int SCALESPEROCTAVE ; 
 scalar_t__ fabs (float) ; 
 TYPE_5__* keypoints ; 
 scalar_t__ malloc (int) ; 

int DetectKeypoint(int numoctaves, ImageOctaves *GaussianPyr)  
{  
	//计算用于DOG极值点检测的主曲率比的阈值  
	double curvature_threshold;  
	curvature_threshold= ((CURVATURE_THRESHOLD + 1)*(CURVATURE_THRESHOLD + 1))/CURVATURE_THRESHOLD;  
#define ImLevels(OCTAVE,LEVEL,ROW,COL) ((float *)(DOGoctaves[(OCTAVE)].Octave[(LEVEL)].Level->data.fl + DOGoctaves[(OCTAVE)].Octave[(LEVEL)].Level->step/sizeof(float) *(ROW)))[(COL)]  

	int   keypoint_count = 0;     
	for (int i=0; i<numoctaves; i++)    
	{          
		for(int j=1;j<SCALESPEROCTAVE+1;j++)//取中间的scaleperoctave个层  
		{    
			//在图像的有效区域内寻找具有显著性特征的局部最大值  
			//float sigma=(GaussianPyr[i].Octave)[j].levelsigma;  
			//int dim = (int) (max(3.0f, 2.0*GAUSSKERN *sigma + 1.0f)*0.5);  
			int dim = (int)(0.5*((GaussianPyr[i].Octave)[j].levelsigmalength)+0.5);  
			for (int m=dim;m<((DOGoctaves[i].row)-dim);m++)   
				for(int n=dim;n<((DOGoctaves[i].col)-dim);n++)  
				{       
					if ( fabs(ImLevels(i,j,m,n))>= CONTRAST_THRESHOLD )  
					{  

						if ( ImLevels(i,j,m,n)!=0.0 )  //1、首先是非零  
						{  
							float inf_val=ImLevels(i,j,m,n);  
							if(( (inf_val <= ImLevels(i,j-1,m-1,n-1))&&  
								(inf_val <= ImLevels(i,j-1,m  ,n-1))&&  
								(inf_val <= ImLevels(i,j-1,m+1,n-1))&&  
								(inf_val <= ImLevels(i,j-1,m-1,n  ))&&  
								(inf_val <= ImLevels(i,j-1,m  ,n  ))&&  
								(inf_val <= ImLevels(i,j-1,m+1,n  ))&&  
								(inf_val <= ImLevels(i,j-1,m-1,n+1))&&  
								(inf_val <= ImLevels(i,j-1,m  ,n+1))&&  
								(inf_val <= ImLevels(i,j-1,m+1,n+1))&&    //底层的小尺度9  

								(inf_val <= ImLevels(i,j,m-1,n-1))&&  
								(inf_val <= ImLevels(i,j,m  ,n-1))&&  
								(inf_val <= ImLevels(i,j,m+1,n-1))&&  
								(inf_val <= ImLevels(i,j,m-1,n  ))&&  
								(inf_val <= ImLevels(i,j,m+1,n  ))&&  
								(inf_val <= ImLevels(i,j,m-1,n+1))&&  
								(inf_val <= ImLevels(i,j,m  ,n+1))&&  
								(inf_val <= ImLevels(i,j,m+1,n+1))&&     //当前层8  

								(inf_val <= ImLevels(i,j+1,m-1,n-1))&&  
								(inf_val <= ImLevels(i,j+1,m  ,n-1))&&  
								(inf_val <= ImLevels(i,j+1,m+1,n-1))&&  
								(inf_val <= ImLevels(i,j+1,m-1,n  ))&&  
								(inf_val <= ImLevels(i,j+1,m  ,n  ))&&  
								(inf_val <= ImLevels(i,j+1,m+1,n  ))&&  
								(inf_val <= ImLevels(i,j+1,m-1,n+1))&&  
								(inf_val <= ImLevels(i,j+1,m  ,n+1))&&  
								(inf_val <= ImLevels(i,j+1,m+1,n+1))     //下一层大尺度9          
								) ||   
								( (inf_val >= ImLevels(i,j-1,m-1,n-1))&&  
								(inf_val >= ImLevels(i,j-1,m  ,n-1))&&  
								(inf_val >= ImLevels(i,j-1,m+1,n-1))&&  
								(inf_val >= ImLevels(i,j-1,m-1,n  ))&&  
								(inf_val >= ImLevels(i,j-1,m  ,n  ))&&  
								(inf_val >= ImLevels(i,j-1,m+1,n  ))&&  
								(inf_val >= ImLevels(i,j-1,m-1,n+1))&&  
								(inf_val >= ImLevels(i,j-1,m  ,n+1))&&  
								(inf_val >= ImLevels(i,j-1,m+1,n+1))&&  

								(inf_val >= ImLevels(i,j,m-1,n-1))&&  
								(inf_val >= ImLevels(i,j,m  ,n-1))&&  
								(inf_val >= ImLevels(i,j,m+1,n-1))&&  
								(inf_val >= ImLevels(i,j,m-1,n  ))&&  
								(inf_val >= ImLevels(i,j,m+1,n  ))&&  
								(inf_val >= ImLevels(i,j,m-1,n+1))&&  
								(inf_val >= ImLevels(i,j,m  ,n+1))&&  
								(inf_val >= ImLevels(i,j,m+1,n+1))&&   

								(inf_val >= ImLevels(i,j+1,m-1,n-1))&&  
								(inf_val >= ImLevels(i,j+1,m  ,n-1))&&  
								(inf_val >= ImLevels(i,j+1,m+1,n-1))&&  
								(inf_val >= ImLevels(i,j+1,m-1,n  ))&&  
								(inf_val >= ImLevels(i,j+1,m  ,n  ))&&  
								(inf_val >= ImLevels(i,j+1,m+1,n  ))&&  
								(inf_val >= ImLevels(i,j+1,m-1,n+1))&&  
								(inf_val >= ImLevels(i,j+1,m  ,n+1))&&  
								(inf_val >= ImLevels(i,j+1,m+1,n+1))   
								) )      //2、满足26个中极值点  
							{     
								//此处可存储  
								//然后必须具有明显的显著性，即必须大于CONTRAST_THRESHOLD=0.02  
								if ( fabs(ImLevels(i,j,m,n))>= CONTRAST_THRESHOLD )  
								{  
									//最后显著处的特征点必须具有足够的曲率比，CURVATURE_THRESHOLD=10.0，首先计算Hessian矩阵  
									// Compute the entries of the Hessian matrix at the extrema location.  
									/* 
									1   0   -1 
									0   0   0 
									-1   0   1         *0.25 
									*/  
									// Compute the trace and the determinant of the Hessian.  
									//Tr_H = Dxx + Dyy;  
									//Det_H = Dxx*Dyy - Dxy^2;  
									float Dxx,Dyy,Dxy,Tr_H,Det_H,curvature_ratio;  
									Dxx = ImLevels(i,j,m,n-1) + ImLevels(i,j,m,n+1)-2.0*ImLevels(i,j,m,n);  
									Dyy = ImLevels(i,j,m-1,n) + ImLevels(i,j,m+1,n)-2.0*ImLevels(i,j,m,n);  
									Dxy = ImLevels(i,j,m-1,n-1) + ImLevels(i,j,m+1,n+1) - ImLevels(i,j,m+1,n-1) - ImLevels(i,j,m-1,n+1);  
									Tr_H = Dxx + Dyy;  
									Det_H = Dxx*Dyy - Dxy*Dxy;  
									// Compute the ratio of the principal curvatures.  
									curvature_ratio = (1.0*Tr_H*Tr_H)/Det_H;  
									if ( (Det_H>=0.0) && (curvature_ratio <= curvature_threshold) )  //最后得到最具有显著性特征的特征点  
									{  
										//将其存储起来，以计算后面的特征描述字  
										keypoint_count++;  
										Keypoint k;  
										/* Allocate memory for the keypoint. */  
										k = (Keypoint) malloc(sizeof(struct KeypointSt));  
										k->next = keypoints;  
										keypoints = k;  
										k->row = m*(GaussianPyr[i].subsample);  
										k->col =n*(GaussianPyr[i].subsample);  
										k->sy = m;    //行  
										k->sx = n;    //列  
										k->octave=i;  
										k->level=j;  
										k->scale = (GaussianPyr[i].Octave)[j].absolute_sigma;        
									}//if >curvature_thresh  
								}//if >contrast  
							}//if inf value  
						}//if non zero  
					}//if >contrast  
				}  //for concrete image level col  
		}//for levels  
	}//for octaves  
	return keypoint_count;  
}