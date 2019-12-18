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
 float* alloca (int) ; 

void vorbis_lpc_predict(float *coeff,float *prime,int m,
                     float *data,long n){

  /* in: coeff[0...m-1] LPC coefficients
         prime[0...m-1] initial values (allocated size of n+m-1)
    out: data[0...n-1] data samples */

  long i,j,o,p;
  float y;
  float *work=alloca(sizeof(*work)*(m+n));

  if(!prime)
    for(i=0;i<m;i++)
      work[i]=0.f;
  else
    for(i=0;i<m;i++)
      work[i]=prime[i];

  for(i=0;i<n;i++){
    y=0;
    o=i;
    p=m;
    for(j=0;j<m;j++)
      y-=work[o++]*coeff[--p];

    data[i]=work[o]=y;
  }
}