#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int* log; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 unsigned int rs_gmul (TYPE_1__ const*,unsigned char,unsigned char const) ; 
 unsigned char rs_hgmul (TYPE_1__ const*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  rs_init_lambda (TYPE_1__ const*,unsigned char*,int,unsigned char const*,int,int) ; 
 int /*<<< orphan*/  rs_poly_copy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rs_poly_mul_x (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rs_poly_mult (TYPE_1__ const*,unsigned char*,int,unsigned char*,int,unsigned char const*,int) ; 

__attribute__((used)) static int rs_modified_berlekamp_massey(const rs_gf256 *_gf,
 unsigned char *_lambda,const unsigned char *_s,unsigned char *_omega,int _npar,
 const unsigned char *_erasures,int _nerasures,int _ndata){
  unsigned char tt[256];
  int           n;
  int           l;
  int           k;
  int           i;
  /*Initialize _lambda, the error locator-polynomial, with the location of
     known erasures.*/
  rs_init_lambda(_gf,_lambda,_npar,_erasures,_nerasures,_ndata);
  rs_poly_copy(tt,_lambda,_npar+1);
  l=_nerasures;
  k=0;
  for(n=_nerasures+1;n<=_npar;n++){
    unsigned d;
    rs_poly_mul_x(tt,tt,n-k+1);
    d=0;
    for(i=0;i<=l;i++)d^=rs_gmul(_gf,_lambda[i],_s[n-1-i]);
    if(d!=0){
      unsigned logd;
      logd=_gf->log[d];
      if(l<n-k){
        int t;
        for(i=0;i<=n-k;i++){
          unsigned tti;
          tti=tt[i];
          tt[i]=rs_hgmul(_gf,_lambda[i],255-logd);
          _lambda[i]=_lambda[i]^rs_hgmul(_gf,tti,logd);
        }
        t=n-k;
        k=n-l;
        l=t;
      }
      else for(i=0;i<=l;i++)_lambda[i]=_lambda[i]^rs_hgmul(_gf,tt[i],logd);
    }
  }
  rs_poly_mult(_gf,_omega,_npar,_lambda,l+1,_s,_npar);
  return l;
}