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
 unsigned int gf16_div (unsigned int,unsigned int) ; 
 unsigned int gf16_mul (unsigned int,unsigned int) ; 

__attribute__((used)) static int bch15_5_calc_omega(unsigned _o[3],unsigned _s[3]){
  unsigned s02;
  unsigned tt;
  unsigned dd;
  int      d;
  _o[0]=_s[0];
  s02=gf16_mul(_s[0],_s[0]);
  dd=_s[1]^gf16_mul(_s[0],s02);
  tt=_s[2]^gf16_mul(s02,_s[1]);
  _o[1]=dd?gf16_div(tt,dd):0;
  _o[2]=dd^gf16_mul(_s[0],_o[1]);
  for(d=3;d>0&&!_o[d-1];d--);
  return d;
}