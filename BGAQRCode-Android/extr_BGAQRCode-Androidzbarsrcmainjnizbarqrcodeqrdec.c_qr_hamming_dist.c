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

__attribute__((used)) static int qr_hamming_dist(unsigned _y1,unsigned _y2,int _maxdiff){
  unsigned y;
  int      ret;
  y=_y1^_y2;
  for(ret=0;ret<_maxdiff&&y;ret++)y&=y-1;
  return ret;
}