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
 float** vwin ; 

void _vorbis_apply_window(float *d,int *winno,long *blocksizes,
                          int lW,int W,int nW){
  lW=(W?lW:0);
  nW=(W?nW:0);

  {
    const float *windowLW=vwin[winno[lW]];
    const float *windowNW=vwin[winno[nW]];

    long n=blocksizes[W];
    long ln=blocksizes[lW];
    long rn=blocksizes[nW];

    long leftbegin=n/4-ln/4;
    long leftend=leftbegin+ln/2;

    long rightbegin=n/2+n/4-rn/4;
    long rightend=rightbegin+rn/2;

    int i,p;

    for(i=0;i<leftbegin;i++)
      d[i]=0.f;

    for(p=0;i<leftend;i++,p++)
      d[i]*=windowLW[p];

    for(i=rightbegin,p=rn/2-1;i<rightend;i++,p--)
      d[i]*=windowNW[p];

    for(;i<n;i++)
      d[i]=0.f;
  }
}