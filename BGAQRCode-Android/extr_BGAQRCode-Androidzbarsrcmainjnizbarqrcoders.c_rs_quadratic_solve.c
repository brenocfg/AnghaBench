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
struct TYPE_7__ {unsigned int* log; unsigned int* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 unsigned int rs_gdiv (TYPE_1__ const*,unsigned int,unsigned int) ; 
 unsigned int rs_gmul (TYPE_1__ const*,unsigned int,unsigned int) ; 
 unsigned char rs_gsqrt (TYPE_1__ const*,unsigned int) ; 
 unsigned int rs_hgmul (TYPE_1__ const*,unsigned int,unsigned int) ; 

__attribute__((used)) static int rs_quadratic_solve(const rs_gf256 *_gf,unsigned _b,unsigned _c,
 unsigned char _x[2]){
  unsigned b;
  unsigned logb;
  unsigned logb2;
  unsigned logb4;
  unsigned logb8;
  unsigned logb12;
  unsigned logb14;
  unsigned logc;
  unsigned logc2;
  unsigned logc4;
  unsigned c8;
  unsigned g3;
  unsigned z3;
  unsigned l3;
  unsigned c0;
  unsigned g2;
  unsigned l2;
  unsigned z2;
  int      inc;
  /*If _b is zero, all we need is a square root.*/
  if(!_b){
    _x[0]=rs_gsqrt(_gf,_c);
    return 1;
  }
  /*If _c is zero, 0 and _b are the roots.*/
  if(!_c){
    _x[0]=0;
    _x[1]=_b;
    return 2;
  }
  logb=_gf->log[_b];
  logc=_gf->log[_c];
  /*If _b lies in GF(2**4), scale x to move it out.*/
  inc=logb%(255/15)==0;
  if(inc){
    b=_gf->exp[logb+254];
    logb=_gf->log[b];
    _c=_gf->exp[logc+253];
    logc=_gf->log[_c];
  }
  else b=_b;
  logb2=_gf->log[_gf->exp[logb<<1]];
  logb4=_gf->log[_gf->exp[logb2<<1]];
  logb8=_gf->log[_gf->exp[logb4<<1]];
  logb12=_gf->log[_gf->exp[logb4+logb8]];
  logb14=_gf->log[_gf->exp[logb2+logb12]];
  logc2=_gf->log[_gf->exp[logc<<1]];
  logc4=_gf->log[_gf->exp[logc2<<1]];
  c8=_gf->exp[logc4<<1];
  g3=rs_hgmul(_gf,
   _gf->exp[logb14+logc]^_gf->exp[logb12+logc2]^_gf->exp[logb8+logc4]^c8,logb);
  /*If g3 doesn't lie in GF(2**4), then our roots lie in an extension field.
    Note that we rely on the fact that _gf->log[0]==0 here.*/
  if(_gf->log[g3]%(255/15)!=0)return 0;
  /*Construct the corresponding quadratic in GF(2**4):
    x**2 + x/alpha**(255/15) + l3/alpha**(2*(255/15))*/
  z3=rs_gdiv(_gf,g3,_gf->exp[logb8<<1]^b);
  l3=rs_hgmul(_gf,rs_gmul(_gf,z3,z3)^rs_hgmul(_gf,z3,logb)^_c,255-logb2);
  c0=rs_hgmul(_gf,l3,255-2*(255/15));
  /*Construct the corresponding quadratic in GF(2**2):
    x**2 + x/alpha**(255/3) + l2/alpha**(2*(255/3))*/
  g2=rs_hgmul(_gf,
   rs_hgmul(_gf,c0,255-2*(255/15))^rs_gmul(_gf,c0,c0),255-255/15);
  z2=rs_gdiv(_gf,g2,_gf->exp[255-(255/15)*4]^_gf->exp[255-(255/15)]);
  l2=rs_hgmul(_gf,
   rs_gmul(_gf,z2,z2)^rs_hgmul(_gf,z2,255-(255/15))^c0,2*(255/15));
  /*Back substitute to the solution in the original field.*/
  _x[0]=_gf->exp[_gf->log[z3^rs_hgmul(_gf,
   rs_hgmul(_gf,l2,255/3)^rs_hgmul(_gf,z2,255/15),logb)]+inc];
  _x[1]=_x[0]^_b;
  return 2;
}