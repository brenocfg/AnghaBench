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
 unsigned char rs_hgmul (TYPE_1__ const*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  rs_poly_zero (unsigned char*,int) ; 

void rs_compute_genpoly(const rs_gf256 *_gf,int _m0,
 unsigned char *_genpoly,int _npar){
  int i;
  if(_npar<=0)return;
  rs_poly_zero(_genpoly,_npar);
  _genpoly[0]=1;
  /*Multiply by (x+alpha^i) for i = 1 ... _ndata.*/
  for(i=0;i<_npar;i++){
    unsigned alphai;
    int      n;
    int      j;
    n=i+1<_npar-1?i+1:_npar-1;
    alphai=_gf->log[_gf->exp[_m0+i]];
    for(j=n;j>0;j--)_genpoly[j]=_genpoly[j-1]^rs_hgmul(_gf,_genpoly[j],alphai);
    _genpoly[0]=rs_hgmul(_gf,_genpoly[0],alphai);
  }
}