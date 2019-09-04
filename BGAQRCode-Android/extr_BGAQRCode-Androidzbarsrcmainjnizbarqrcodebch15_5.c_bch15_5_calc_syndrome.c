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
 unsigned int* gf16_exp ; 

__attribute__((used)) static int bch15_5_calc_syndrome(unsigned _s[3],unsigned _y){
  unsigned p;
  int      i;
  int      j;
  p=0;
  for(i=0;i<15;i++)if(_y&1<<i)p^=gf16_exp[i];
  _s[0]=p;
  p=0;
  for(i=0;i<3;i++)for(j=0;j<5;j++)if(_y&1<<5*i+j)p^=gf16_exp[j*3];
  _s[1]=p;
  p=0;
  for(i=0;i<5;i++)for(j=0;j<3;j++)if(_y&1<<3*i+j)p^=gf16_exp[j*5];
  _s[2]=p;
  return _s[0]!=0||_s[1]!=0||_s[2]!=0;
}