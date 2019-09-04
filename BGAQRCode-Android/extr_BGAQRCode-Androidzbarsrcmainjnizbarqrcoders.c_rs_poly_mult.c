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
 int /*<<< orphan*/  rs_poly_zero (unsigned char*,int) ; 

__attribute__((used)) static void rs_poly_mult(const rs_gf256 *_gf,unsigned char *_p,int _dp1,
 const unsigned char *_q,int _ep1,const unsigned char *_r,int _fp1){
  int m;
  int i;
  rs_poly_zero(_p,_dp1);
  m=_ep1<_dp1?_ep1:_dp1;
  for(i=0;i<m;i++)if(_q[i]!=0){
    unsigned logqi;
    int      n;
    int      j;
    n=_dp1-i<_fp1?_dp1-i:_fp1;
    logqi=_gf->log[_q[i]];
    for(j=0;j<n;j++)_p[i+j]^=rs_hgmul(_gf,_r[j],logqi);
  }
}