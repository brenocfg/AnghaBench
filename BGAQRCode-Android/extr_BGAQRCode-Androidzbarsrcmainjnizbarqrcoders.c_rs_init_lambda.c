#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rs_gf256 ;

/* Variables and functions */
 unsigned char rs_hgmul (int /*<<< orphan*/  const*,unsigned char,int) ; 
 int /*<<< orphan*/  rs_poly_zero (unsigned char*,int) ; 

__attribute__((used)) static void rs_init_lambda(const rs_gf256 *_gf,unsigned char *_lambda,int _npar,
 const unsigned char *_erasures,int _nerasures,int _ndata){
  int i;
  int j;
  rs_poly_zero(_lambda,(_npar<4?4:_npar)+1);
  _lambda[0]=1;
  for(i=0;i<_nerasures;i++)for(j=i+1;j>0;j--){
    _lambda[j]^=rs_hgmul(_gf,_lambda[j-1],_ndata-1-_erasures[i]);
  }
}