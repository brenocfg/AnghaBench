#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* log; unsigned int* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 unsigned int rs_gdiv (TYPE_1__ const*,unsigned int,unsigned int) ; 
 unsigned int rs_gmul (TYPE_1__ const*,unsigned int,unsigned int) ; 
 int rs_quadratic_solve (TYPE_1__ const*,unsigned int,int,unsigned char*) ; 

__attribute__((used)) static int rs_cubic_solve(const rs_gf256 *_gf,
 unsigned _a,unsigned _b,unsigned _c,unsigned char _x[3]){
  unsigned k;
  unsigned logd;
  unsigned d2;
  unsigned logd2;
  unsigned logw;
  int      nroots;
  /*If _c is zero, factor out the 0 root.*/
  if(!_c){
    nroots=rs_quadratic_solve(_gf,_a,_b,_x);
    if(_b)_x[nroots++]=0;
    return nroots;
  }
  /*Substitute x=_a+y*sqrt(_a**2+_b) to get y**3 + y + k == 0,
     k = (_a*_b+c)/(_a**2+b)**(3/2).*/
  k=rs_gmul(_gf,_a,_b)^_c;
  d2=rs_gmul(_gf,_a,_a)^_b;
  if(!d2){
    int logx;
    if(!k){
      /*We have a triple root.*/
      _x[0]=_a;
      return 1;
    }
    logx=_gf->log[k];
    if(logx%3!=0)return 0;
    logx/=3;
    _x[0]=_a^_gf->exp[logx];
    _x[1]=_a^_gf->exp[logx+255/3];
    _x[2]=_a^_x[0]^_x[1];
    return 3;
  }
  logd2=_gf->log[d2];
  logd=logd2+(255&-(logd2&1))>>1;
  k=rs_gdiv(_gf,k,_gf->exp[logd+logd2]);
  /*Substitute y=w+1/w and z=w**3 to get z**2 + k*z + 1 == 0.*/
  nroots=rs_quadratic_solve(_gf,k,1,_x);
  if(nroots<1){
    /*The Reed-Solomon code is only valid if we can find 3 distinct roots in
       GF(2**8), so if we know there's only one, we don't actually need to find
       it.
      Note that we're also called by the quartic solver, but if we contain a
       non-trivial irreducible factor, than so does the original
       quartic~\cite{LW72}, and failing to return a root here actually saves us
       some work there, also.*/
    return 0;
  }
  /*Recover w from z.*/
  logw=_gf->log[_x[0]];
  if(logw){
    if(logw%3!=0)return 0;
    logw/=3;
    /*Recover x from w.*/
    _x[0]=_gf->exp[_gf->log[_gf->exp[logw]^_gf->exp[255-logw]]+logd]^_a;
    logw+=255/3;
    _x[1]=_gf->exp[_gf->log[_gf->exp[logw]^_gf->exp[255-logw]]+logd]^_a;
    _x[2]=_x[0]^_x[1]^_a;
    return 3;
  }
  else{
    _x[0]=_a;
    /*In this case _x[1] is a double root, so we know the Reed-Solomon code is
       invalid.
      Note that we still have to return at least one root, because if we're
       being called by the quartic solver, the quartic might still have 4
       distinct roots.
      But we don't need more than one root, so we can avoid computing the
       expensive one.*/
    /*_x[1]=_gf->exp[_gf->log[_gf->exp[255/3]^_gf->exp[2*(255/3)]]+logd]^_a;*/
    return 1;
  }
}