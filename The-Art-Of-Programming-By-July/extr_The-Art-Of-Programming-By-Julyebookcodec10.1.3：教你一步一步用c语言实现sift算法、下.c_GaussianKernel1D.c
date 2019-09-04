#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 double CV_PI ; 
 float exp (double) ; 
 scalar_t__ malloc (int) ; 
 float sqrt (double) ; 

float* GaussianKernel1D(float sigma, int dim)   
{  

	unsigned int i;  
	//printf("GaussianKernel1D(): Creating 1x%d vector for sigma=%.3f gaussian kernel/n", dim, sigma);  

	float *kern=(float*)malloc( dim*sizeof(float) );  
	float s2 = sigma * sigma;  
	int c = dim / 2;  
	float m= 1.0/(sqrt(2.0 * CV_PI) * sigma);  
	double v;   
	for ( i = 0; i < (dim + 1) / 2; i++)   
	{  
		v = m * exp(-(1.0*i*i)/(2.0 * s2)) ;  
		kern[c+i] = v;  
		kern[c-i] = v;  
	}  
	//   normalizeVec(kern, dim);  
	// for ( i = 0; i < dim; i++)  
	//  printf("%f  ", kern[i]);  
	//  printf("/n");  
	return kern;  
}