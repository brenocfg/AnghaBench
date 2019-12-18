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
typedef  unsigned char const uint32_t ;

/* Variables and functions */

uint32_t dtoverlay_read_u32(const void *src, int off)
{
   const unsigned char *p = src;
   return (p[off + 0] << 24) | (p[off + 1] << 16) |
          (p[off + 2] << 8)  | (p[off + 3] << 0);
}