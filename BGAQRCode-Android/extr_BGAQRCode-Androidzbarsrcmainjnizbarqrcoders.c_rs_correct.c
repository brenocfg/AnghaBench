#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int* log; size_t* exp; } ;
typedef  TYPE_1__ rs_gf256 ;

/* Variables and functions */
 int /*<<< orphan*/  rs_calc_syndrome (TYPE_1__ const*,int,unsigned char*,int,unsigned char*,int) ; 
 int rs_find_roots (TYPE_1__ const*,unsigned char*,unsigned char*,int,int) ; 
 unsigned char rs_gdiv (TYPE_1__ const*,unsigned int,unsigned int) ; 
 unsigned int rs_hgmul (TYPE_1__ const*,unsigned char,unsigned int) ; 
 int rs_modified_berlekamp_massey (TYPE_1__ const*,unsigned char*,unsigned char*,unsigned char*,int,unsigned char const*,int,int) ; 

int rs_correct(const rs_gf256 *_gf,int _m0,unsigned char *_data,int _ndata,
 int _npar,const unsigned char *_erasures,int _nerasures){
  /*lambda must have storage for at least five entries to avoid special cases
     in the low-degree polynomial solver.*/
  unsigned char lambda[256];
  unsigned char omega[256];
  unsigned char epos[256];
  unsigned char s[256];
  int           i;
  /*If we already have too many erasures, we can't possibly succeed.*/
  if(_nerasures>_npar)return -1;
  /*Compute the syndrome values.*/
  rs_calc_syndrome(_gf,_m0,s,_npar,_data,_ndata);
  /*Check for a non-zero value.*/
  for(i=0;i<_npar;i++)if(s[i]){
    int nerrors;
    int j;
    /*Construct the error locator polynomial.*/
    nerrors=rs_modified_berlekamp_massey(_gf,lambda,s,omega,_npar,
     _erasures,_nerasures,_ndata);
    /*If we can't locate any errors, we can't force the syndrome values to
       zero, and must have a decoding error.
      Conversely, if we have too many errors, there's no reason to even attempt
       the root search.*/
    if(nerrors<=0||nerrors-_nerasures>_npar-_nerasures>>1)return -1;
    /*Compute the locations of the errors.
      If they are not all distinct, or some of them were outside the valid
       range for our block size, we have a decoding error.*/
    if(rs_find_roots(_gf,epos,lambda,nerrors,_ndata)<nerrors)return -1;
    /*Now compute the error magnitudes.*/
    for(i=0;i<nerrors;i++){
      unsigned a;
      unsigned b;
      unsigned alpha;
      unsigned alphan1;
      unsigned alphan2;
      unsigned alphanj;
      alpha=epos[i];
      /*Evaluate omega at alpha**-1.*/
      a=0;
      alphan1=255-alpha;
      alphanj=0;
      for(j=0;j<_npar;j++){
        a^=rs_hgmul(_gf,omega[j],alphanj);
        alphanj=_gf->log[_gf->exp[alphanj+alphan1]];
      }
      /*Evaluate the derivative of lambda at alpha**-1
        All the odd powers vanish.*/
      b=0;
      alphan2=_gf->log[_gf->exp[alphan1<<1]];
      alphanj=alphan1+_m0*alpha%255;
      for(j=1;j<=_npar;j+=2){
        b^=rs_hgmul(_gf,lambda[j],alphanj);
        alphanj=_gf->log[_gf->exp[alphanj+alphan2]];
      }
      /*Apply the correction.*/
      _data[_ndata-1-alpha]^=rs_gdiv(_gf,a,b);
    }
    return nerrors;
  }
  return 0;
}