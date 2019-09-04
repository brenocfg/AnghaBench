#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int rows; double cols; } ;
struct TYPE_18__ {float levelsigma; float absolute_sigma; int levelsigmalength; TYPE_3__* Level; } ;
struct TYPE_17__ {int col; int row; double subsample; TYPE_2__* Octave; } ;
typedef  TYPE_1__ ImageOctaves ;
typedef  TYPE_2__ ImageLevels ;
typedef  TYPE_3__ CvMat ;

/* Variables and functions */
 int BlurImage (TYPE_3__*,TYPE_3__*,float) ; 
 int /*<<< orphan*/  CV_32FC1 ; 
 TYPE_1__* DOGoctaves ; 
 scalar_t__ DOUBLE_BASE_IMAGE_SIZE ; 
 double MAXOCTAVES ; 
 int SCALESPEROCTAVE ; 
 TYPE_3__* cvCloneMat (TYPE_3__*) ; 
 TYPE_3__* cvCreateMat (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvSub (TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* halfSizeImage (TYPE_3__*) ; 
 int log (double) ; 
 scalar_t__ malloc (int) ; 
 int min (int,double) ; 
 double pow (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 float sqrt (double) ; 

ImageOctaves* BuildGaussianOctaves(CvMat * image)   
{  
	ImageOctaves *octaves;  
	CvMat *tempMat;  
	CvMat *dst;  
	CvMat *temp;  

	int i,j;  
	double k = pow(2, 1.0/((float)SCALESPEROCTAVE));  //方差倍数  
	float preblur_sigma, initial_sigma , sigma1,sigma2,sigma,absolute_sigma,sigma_f;  
	//计算金字塔的阶梯数目  
	int dim = min(image->rows, image->cols);  
	int numoctaves = (int) (log((double) dim) / log(2.0)) - 2;    //金字塔阶数  
	//限定金字塔的阶梯数  
	numoctaves = min(numoctaves, MAXOCTAVES);  
	//为高斯金塔和DOG金字塔分配内存  
	octaves=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves) );  
	DOGoctaves=(ImageOctaves*) malloc( numoctaves * sizeof(ImageOctaves) );  

	printf("BuildGaussianOctaves(): Base image dimension is %dx%d/n", (int)(0.5*(image->cols)), (int)(0.5*(image->rows)) );  
	printf("BuildGaussianOctaves(): Building %d octaves/n", numoctaves);  

	// start with initial source image  
	tempMat=cvCloneMat( image );  
	// preblur_sigma = 1.0;//sqrt(2 - 4*INITSIGMA*INITSIGMA);  
	initial_sigma = sqrt(2);//sqrt( (4*INITSIGMA*INITSIGMA) + preblur_sigma * preblur_sigma );  
	//   initial_sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);  

	//在每一阶金字塔图像中建立不同的尺度图像  
	for ( i = 0; i < numoctaves; i++)   
	{     
		//首先建立金字塔每一阶梯的最底层，其中0阶梯的最底层已经建立好  
		printf("Building octave %d of dimesion (%d, %d)/n", i, tempMat->cols,tempMat->rows);  
		//为各个阶梯分配内存  
		octaves[i].Octave= (ImageLevels*) malloc( (SCALESPEROCTAVE + 3) * sizeof(ImageLevels) );  
		DOGoctaves[i].Octave= (ImageLevels*) malloc( (SCALESPEROCTAVE + 2) * sizeof(ImageLevels) );  
		//存储各个阶梯的最底层  
		(octaves[i].Octave)[0].Level=tempMat;  

		octaves[i].col=tempMat->cols;  
		octaves[i].row=tempMat->rows;  
		DOGoctaves[i].col=tempMat->cols;  
		DOGoctaves[i].row=tempMat->rows;  
		if (DOUBLE_BASE_IMAGE_SIZE)  
			octaves[i].subsample=pow(2,i)*0.5;  
		else  
			octaves[i].subsample=pow(2,i);  

		if(i==0)       
		{  
			(octaves[0].Octave)[0].levelsigma = initial_sigma;  
			(octaves[0].Octave)[0].absolute_sigma = initial_sigma;  
			printf("0 scale and blur sigma : %f /n", (octaves[0].subsample) * ((octaves[0].Octave)[0].absolute_sigma));  
		}  
		else  
		{  
			(octaves[i].Octave)[0].levelsigma = (octaves[i-1].Octave)[SCALESPEROCTAVE].levelsigma;  
			(octaves[i].Octave)[0].absolute_sigma = (octaves[i-1].Octave)[SCALESPEROCTAVE].absolute_sigma;  
			printf( "0 scale and blur sigma : %f /n", ((octaves[i].Octave)[0].absolute_sigma) );  
		}  
		sigma = initial_sigma;  
		//建立本阶梯其他层的图像  
		for ( j =  1; j < SCALESPEROCTAVE + 3; j++)   
		{  
			dst = cvCreateMat(tempMat->rows, tempMat->cols, CV_32FC1);//用于存储高斯层  
			temp = cvCreateMat(tempMat->rows, tempMat->cols, CV_32FC1);//用于存储DOG层  
			// 2 passes of 1D on original  
			//   if(i!=0)  
			//   {  
			//       sigma1 = pow(k, j - 1) * ((octaves[i-1].Octave)[j-1].levelsigma);  
			//          sigma2 = pow(k, j) * ((octaves[i].Octave)[j-1].levelsigma);  
			//       sigma = sqrt(sigma2*sigma2 - sigma1*sigma1);  
			sigma_f= sqrt(k*k-1)*sigma;  
			//   }  
			//   else  
			//   {  
			//       sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4)*pow(k,j);  
			//   }    
			sigma = k*sigma;  
			absolute_sigma = sigma * (octaves[i].subsample);  
			printf("%d scale and Blur sigma: %f  /n", j, absolute_sigma);  

			(octaves[i].Octave)[j].levelsigma = sigma;  
			(octaves[i].Octave)[j].absolute_sigma = absolute_sigma;  
			//产生高斯层  
			int length=BlurImage((octaves[i].Octave)[j-1].Level, dst, sigma_f);//相应尺度  
			(octaves[i].Octave)[j].levelsigmalength = length;  
			(octaves[i].Octave)[j].Level=dst;  
			//产生DOG层  
			cvSub( ((octaves[i].Octave)[j]).Level, ((octaves[i].Octave)[j-1]).Level, temp, 0 );  
			//         cvAbsDiff( ((octaves[i].Octave)[j]).Level, ((octaves[i].Octave)[j-1]).Level, temp );  
			((DOGoctaves[i].Octave)[j-1]).Level=temp;  
		}  
		// halve the image size for next iteration  
		tempMat  = halfSizeImage( ( (octaves[i].Octave)[SCALESPEROCTAVE].Level ) );  
	}  
	return octaves;  
}