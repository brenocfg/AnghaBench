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
 scalar_t__ thumb_mode ; 

__attribute__((used)) static unsigned
neon_dp_fixup (unsigned i)
{
  if (thumb_mode)
    {
      /* The U bit is at bit 24 by default. Move to bit 28 in Thumb mode.  */
      if (i & (1 << 24))
        i |= 1 << 28;
      
      i &= ~(1 << 24);
      
      i |= 0xef000000;
    }
  else
    i |= 0xf2000000;
  
  return i;
}