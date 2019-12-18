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
 float fabs (float) ; 

__attribute__((used)) static void flag_lossless(int limit, float prepoint, float postpoint, float *mdct,
                         float *floor, int *flag, int i, int jn){
  int j;
  for(j=0;j<jn;j++){
    float point = j>=limit-i ? postpoint : prepoint;
    float r = fabs(mdct[j])/floor[j];
    if(r<point)
      flag[j]=0;
    else
      flag[j]=1;
  }
}