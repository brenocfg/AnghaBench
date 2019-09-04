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

/* Variables and functions */
 int bch15_5_calc_epos (unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  bch15_5_calc_syndrome (unsigned int*,unsigned int) ; 
 unsigned int bch15_5_encode (unsigned int) ; 

int bch15_5_correct(unsigned *_y){
  unsigned s[3];
  unsigned epos[3];
  unsigned y;
  int      nerrors;
  int      i;
  y=*_y;
  if(!bch15_5_calc_syndrome(s,y))return 0;
  nerrors=bch15_5_calc_epos(epos,s);
  if(nerrors>0){
    /*If we had a non-zero syndrome value, we should always find at least one
       error location, or we've got a decoding error.*/
    for(i=0;i<nerrors;i++)y^=1<<epos[i];
    /*If there were too many errors, we may not find enough roots to reduce the
       syndrome to zero.
      We could recompute it to check, but it's much faster just to check that
       we have a valid codeword.*/
    if(bch15_5_encode(y>>10)==y){
      /*Decoding succeeded.*/
      *_y=y;
      return nerrors;
    }
  }
  /*Decoding failed due to too many bit errors.*/
  return -1;
}