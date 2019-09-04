#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int* log; size_t* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 unsigned int rs_hgmul (TYPE_1__ const*,unsigned char const,unsigned int) ; 
 int rs_quartic_solve (TYPE_1__ const*,unsigned char const,unsigned char const,unsigned char const,unsigned char const,unsigned char*) ; 

__attribute__((used)) static int rs_find_roots(const rs_gf256 *_gf,unsigned char *_epos,
 const unsigned char *_lambda,int _nerrors,int _ndata){
  unsigned alpha;
  int      nroots;
  int      i;
  nroots=0;
  if(_nerrors<=4){
    /*Explicit solutions for higher degrees are possible.
      Chien uses large lookup tables to solve quintics, and Truong et al. give
       special algorithms for degree up through 11, though they use exhaustive
       search (with reduced complexity) for some portions.
      Quartics are good enough for reading CDs, and represent a reasonable code
       complexity trade-off without requiring any extra tables.
      Note that _lambda[0] is always 1.*/
    _nerrors=rs_quartic_solve(_gf,_lambda[1],_lambda[2],_lambda[3],_lambda[4],
     _epos);
    for(i=0;i<_nerrors;i++)if(_epos[i]){
      alpha=_gf->log[_epos[i]];
      if((int)alpha<_ndata)_epos[nroots++]=alpha;
    }
    return nroots;
  }
  else for(alpha=0;(int)alpha<_ndata;alpha++){
    unsigned alphai;
    unsigned sum;
    sum=0;
    alphai=0;
    for(i=0;i<=_nerrors;i++){
      sum^=rs_hgmul(_gf,_lambda[_nerrors-i],alphai);
      alphai=_gf->log[_gf->exp[alphai+alpha]];
    }
    if(!sum)_epos[nroots++]=alpha;
  }
  return nroots;
}