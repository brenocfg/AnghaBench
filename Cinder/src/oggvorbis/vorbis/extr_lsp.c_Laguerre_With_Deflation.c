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
 double EPSILON ; 
 double* alloca (int) ; 
 int fabs (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static int Laguerre_With_Deflation(float *a,int ord,float *r){
  int i,m;
  double lastdelta=0.f;
  double *defl=alloca(sizeof(*defl)*(ord+1));
  for(i=0;i<=ord;i++)defl[i]=a[i];

  for(m=ord;m>0;m--){
    double new=0.f,delta;

    /* iterate a root */
    while(1){
      double p=defl[m],pp=0.f,ppp=0.f,denom;

      /* eval the polynomial and its first two derivatives */
      for(i=m;i>0;i--){
        ppp = new*ppp + pp;
        pp  = new*pp  + p;
        p   = new*p   + defl[i-1];
      }

      /* Laguerre's method */
      denom=(m-1) * ((m-1)*pp*pp - m*p*ppp);
      if(denom<0)
        return(-1);  /* complex root!  The LPC generator handed us a bad filter */

      if(pp>0){
        denom = pp + sqrt(denom);
        if(denom<EPSILON)denom=EPSILON;
      }else{
        denom = pp - sqrt(denom);
        if(denom>-(EPSILON))denom=-(EPSILON);
      }

      delta  = m*p/denom;
      new   -= delta;

      if(delta<0.f)delta*=-1;

      if(fabs(delta/new)<10e-12)break;
      lastdelta=delta;
    }

    r[m-1]=new;

    /* forward deflation */

    for(i=m;i>0;i--)
      defl[i-1]+=new*defl[i];
    defl++;

  }
  return(0);
}