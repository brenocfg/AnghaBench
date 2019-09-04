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

__attribute__((used)) static void isaac_mix(unsigned _x[8]){
  static const unsigned char SHIFT[8]={11,2,8,16,10,4,8,9};
  int i;
  for(i=0;i<8;i++){
    _x[i]^=_x[i+1&7]<<SHIFT[i];
    _x[i+3&7]+=_x[i];
    _x[i+1&7]+=_x[i+2&7];
    i++;
    _x[i]^=_x[i+1&7]>>SHIFT[i];
    _x[i+3&7]+=_x[i];
    _x[i+1&7]+=_x[i+2&7];
  }
}