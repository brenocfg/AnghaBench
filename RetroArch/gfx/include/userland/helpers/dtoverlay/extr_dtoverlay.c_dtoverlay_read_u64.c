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
typedef  int uint64_t ;

/* Variables and functions */

uint64_t dtoverlay_read_u64(const void *src, int off)
{
   const unsigned char *p = src;
   return ((uint64_t)p[off + 0] << 56) | ((uint64_t)p[off + 1] << 48) |
          ((uint64_t)p[off + 2] << 40)  | ((uint64_t)p[off + 3] << 32) |
          (p[off + 4] << 24) | (p[off + 5] << 16) |
          (p[off + 6] << 8)  | (p[off + 7] << 0);
}