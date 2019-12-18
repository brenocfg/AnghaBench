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
typedef  scalar_t__ u32 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */

void
ScspConvert32uto16s (s32 *srcL, s32 *srcR, s16 *dst, u32 len)
{
  u32 i;

  for (i = 0; i < len; i++)
    {
      // Left Channel
      if (*srcL > 0x7FFF)
        *dst = 0x7FFF;
      else if (*srcL < -0x8000)
        *dst = -0x8000;
      else
        *dst = *srcL;

      srcL++;
      dst++;

      // Right Channel
      if (*srcR > 0x7FFF)
        *dst = 0x7FFF;
      else if (*srcR < -0x8000)
        *dst = -0x8000;
      else
        *dst = *srcR;

      srcR++;
      dst++;
    }
}