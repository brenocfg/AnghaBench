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

unsigned qr_isqrt(unsigned _val){
  unsigned g;
  unsigned b;
  int      bshift;
  /*Uses the second method from
     http://www.azillionmonkeys.com/qed/sqroot.html
    The main idea is to search for the largest binary digit b such that
     (g+b)*(g+b) <= _val, and add it to the solution g.*/
  g=0;
  b=0x8000;
  for(bshift=16;bshift-->0;){
    unsigned t;
    t=(g<<1)+b<<bshift;
    if(t<=_val){
      g+=b;
      _val-=t;
    }
    b>>=1;
  }
  return g;
}