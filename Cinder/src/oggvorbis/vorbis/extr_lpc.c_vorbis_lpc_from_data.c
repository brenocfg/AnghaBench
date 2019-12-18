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
 double* alloca (int) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 

float vorbis_lpc_from_data(float *data,float *lpci,int n,int m){
  double *aut=alloca(sizeof(*aut)*(m+1));
  double *lpc=alloca(sizeof(*lpc)*(m));
  double error;
  double epsilon;
  int i,j;

  /* autocorrelation, p+1 lag coefficients */
  j=m+1;
  while(j--){
    double d=0; /* double needed for accumulator depth */
    for(i=j;i<n;i++)d+=(double)data[i]*data[i-j];
    aut[j]=d;
  }

  /* Generate lpc coefficients from autocorr values */

  /* set our noise floor to about -100dB */
  error=aut[0] * (1. + 1e-10);
  epsilon=1e-9*aut[0]+1e-10;

  for(i=0;i<m;i++){
    double r= -aut[i+1];

    if(error<epsilon){
      memset(lpc+i,0,(m-i)*sizeof(*lpc));
      goto done;
    }

    /* Sum up this iteration's reflection coefficient; note that in
       Vorbis we don't save it.  If anyone wants to recycle this code
       and needs reflection coefficients, save the results of 'r' from
       each iteration. */

    for(j=0;j<i;j++)r-=lpc[j]*aut[i-j];
    r/=error;

    /* Update LPC coefficients and total error */

    lpc[i]=r;
    for(j=0;j<i/2;j++){
      double tmp=lpc[j];

      lpc[j]+=r*lpc[i-1-j];
      lpc[i-1-j]+=r*tmp;
    }
    if(i&1)lpc[j]+=lpc[j]*r;

    error*=1.-r*r;

  }

 done:

  /* slightly damp the filter */
  {
    double g = .99;
    double damp = g;
    for(j=0;j<m;j++){
      lpc[j]*=damp;
      damp*=g;
    }
  }

  for(j=0;j<m;j++)lpci[j]=(float)lpc[j];

  /* we need the error value to know how big an impulse to hit the
     filter with later */

  return error;
}