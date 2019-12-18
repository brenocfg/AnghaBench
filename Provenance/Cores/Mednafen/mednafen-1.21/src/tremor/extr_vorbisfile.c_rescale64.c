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
typedef  int ogg_int64_t ;

/* Variables and functions */

ogg_int64_t rescale64(ogg_int64_t x, ogg_int64_t from, ogg_int64_t to){
  ogg_int64_t frac=0;
  ogg_int64_t ret=0;
  int i;
  if(x >= from) return to;
  if(x <= 0) return 0;

  for(i=0;i<64;i++){
    if(x>=from){
      frac|=1;
      x-=from;
    }
    x<<=1;
    frac<<=1;
  }

  for(i=0;i<64;i++){
    if(frac & 1){
      ret+=to;
    }
    frac>>=1;
    ret>>=1;
  }

  return ret;
}