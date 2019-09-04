#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* log; size_t* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 unsigned char const rs_hgmul (TYPE_1__ const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void rs_calc_syndrome(const rs_gf256 *_gf,int _m0,
 unsigned char *_s,int _npar,const unsigned char *_data,int _ndata){
  int i;
  int j;
  for(j=0;j<_npar;j++){
    unsigned alphaj;
    unsigned sj;
    sj=0;
    alphaj=_gf->log[_gf->exp[j+_m0]];
    for(i=0;i<_ndata;i++)sj=_data[i]^rs_hgmul(_gf,sj,alphaj);
    _s[j]=sj;
  }
}