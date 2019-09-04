#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int* log; unsigned int* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 int rs_cubic_solve (TYPE_1__ const*,unsigned int,unsigned int,unsigned int,unsigned char*) ; 
 unsigned int rs_gdiv (TYPE_1__ const*,unsigned int,unsigned int) ; 
 unsigned int rs_gmul (TYPE_1__ const*,unsigned int,unsigned int) ; 
 unsigned int rs_gsqrt (TYPE_1__ const*,unsigned int) ; 
 unsigned int rs_hgmul (TYPE_1__ const*,unsigned int,unsigned int) ; 
 int rs_quadratic_solve (TYPE_1__ const*,unsigned int,unsigned int,unsigned char*) ; 

__attribute__((used)) static int rs_quartic_solve(const rs_gf256 *_gf,
 unsigned _a,unsigned _b,unsigned _c,unsigned _d,unsigned char _x[3]){
  unsigned r;
  unsigned s;
  unsigned t;
  unsigned b;
  int      nroots;
  int      i;
  /*If _d is zero, factor out the 0 root.*/
  if(!_d){
    nroots=rs_cubic_solve(_gf,_a,_b,_c,_x);
    if(_c)_x[nroots++]=0;
    return nroots;
  }
  if(_a){
    unsigned loga;
    /*Substitute x=(1/y) + sqrt(_c/_a) to eliminate the cubic term.*/
    loga=_gf->log[_a];
    r=rs_hgmul(_gf,_c,255-loga);
    s=rs_gsqrt(_gf,r);
    t=_d^rs_gmul(_gf,_b,r)^rs_gmul(_gf,r,r);
    if(t){
      unsigned logti;
      logti=255-_gf->log[t];
      /*The result is still quartic, but with no cubic term.*/
      nroots=rs_quartic_solve(_gf,0,rs_hgmul(_gf,_b^rs_hgmul(_gf,s,loga),logti),
       _gf->exp[loga+logti],_gf->exp[logti],_x);
      for(i=0;i<nroots;i++)_x[i]=_gf->exp[255-_gf->log[_x[i]]]^s;
    }
    else{
      /*s must be a root~\cite{LW72}, and is in fact a double-root~\cite{CCO69}.
        Thus we're left with only a quadratic to solve.
        @ARTICLE{CCO69,
          author="Robert T. Chien and B. D. Cunningham and I. B. Oldham",
          title="Hybrid Methods for Finding Roots of a Polynomial---With
           Applications to {BCH} Decoding",
          journal="{IEEE} Transactions on Information Theory",
          volume=15,
          number=2,
          pages="329--335",
          month=Mar,
          year=1969
        }*/
      nroots=rs_quadratic_solve(_gf,_a,_b^r,_x);
      /*s may be a triple root if s=_b/_a, but not quadruple, since _a!=0.*/
      if(nroots!=2||_x[0]!=s&&_x[1]!=s)_x[nroots++]=s;
    }
    return nroots;
  }
  /*If there are no odd powers, it's really just a quadratic in disguise.*/
  if(!_c)return rs_quadratic_solve(_gf,rs_gsqrt(_gf,_b),rs_gsqrt(_gf,_d),_x);
  /*Factor into (x**2 + r*x + s)*(x**2 + r*x + t) by solving for r, which can
     be shown to satisfy r**3 + _b*r + _c == 0.*/
  nroots=rs_cubic_solve(_gf,0,_b,_c,_x);
  if(nroots<1){
    /*The Reed-Solomon code is only valid if we can find 4 distinct roots in
       GF(2**8).
      If the cubic does not factor into 3 (possibly duplicate) roots, then we
       know that the quartic must have a non-trivial irreducible factor.*/
    return 0;
  }
  r=_x[0];
  /*Now solve for s and t.*/
  b=rs_gdiv(_gf,_c,r);
  nroots=rs_quadratic_solve(_gf,b,_d,_x);
  if(nroots<2)return 0;
  s=_x[0];
  t=_x[1];
  /*_c=r*(s^t) was non-zero, so s and t must be distinct.
    But if z is a root of z**2 ^ r*z ^ s, then so is (z^r), and s = z*(z^r).
    Hence if z is also a root of z**2 ^ r*z ^ t, then t = s, a contradiction.
    Thus all four roots are distinct, if they exist.*/
  nroots=rs_quadratic_solve(_gf,r,s,_x);
  return nroots+rs_quadratic_solve(_gf,r,t,_x+nroots);
}