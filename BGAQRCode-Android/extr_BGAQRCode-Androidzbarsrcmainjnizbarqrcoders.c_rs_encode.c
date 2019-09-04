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
struct TYPE_4__ {unsigned int* log; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 unsigned char rs_hgmul (TYPE_1__ const*,unsigned char const,unsigned int) ; 
 int /*<<< orphan*/  rs_poly_div_x (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rs_poly_zero (unsigned char*,int) ; 

void rs_encode(const rs_gf256 *_gf,unsigned char *_data,int _ndata,
 const unsigned char *_genpoly,int _npar){
  unsigned char *lfsr;
  unsigned       d;
  int            i;
  int            j;
  if(_npar<=0)return;
  lfsr=_data+_ndata-_npar;
  rs_poly_zero(lfsr,_npar);
  for(i=0;i<_ndata-_npar;i++){
    d=_data[i]^lfsr[0];
    if(d){
      unsigned logd;
      logd=_gf->log[d];
      for(j=0;j<_npar-1;j++){
        lfsr[j]=lfsr[j+1]^rs_hgmul(_gf,_genpoly[_npar-1-j],logd);
      }
      lfsr[_npar-1]=rs_hgmul(_gf,_genpoly[0],logd);
    }
    else rs_poly_div_x(lfsr,lfsr,_npar);
  }
}