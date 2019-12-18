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
typedef  int uint32_t ;
typedef  int u ;

/* Variables and functions */

uint32_t __bswapsi2(uint32_t u) {
  return ((((u)&0xff000000) >> 24) |
          (((u)&0x00ff0000) >> 8)  |
          (((u)&0x0000ff00) << 8)  |
          (((u)&0x000000ff) << 24));
}