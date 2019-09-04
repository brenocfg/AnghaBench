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
 int bch15_5_calc_omega (unsigned int*,unsigned int*) ; 
 size_t* gf16_exp ; 
 size_t gf16_hmul (unsigned int,int) ; 
 void** gf16_log ; 

__attribute__((used)) static int bch15_5_calc_epos(unsigned _epos[3],unsigned _s[3]){
  unsigned o[3];
  int      nerrors;
  int      d;
  int      i;
  d=bch15_5_calc_omega(o,_s);
  nerrors=0;
  if(d==1)_epos[nerrors++]=gf16_log[o[0]];
  else if(d>0){
    for(i=0;i<15;i++){
      int i2;
      i2=gf16_log[gf16_exp[i<<1]];
      if(!(gf16_exp[i+i2]^gf16_hmul(o[0],i2)^gf16_hmul(o[1],i)^o[2])){
        _epos[nerrors++]=i;
      }
    }
    if(nerrors<d)return -1;
  }
  return nerrors;
}