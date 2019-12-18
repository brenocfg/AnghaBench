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
 int* sprite_window_mask ; 
 int vdp2width ; 

int TestSpriteWindow(int wctl, int x, int y)
{
   int mask;
   int addr = (y*vdp2width) + x;

   if (addr >= (704 * 512))
      return 0;

   mask = sprite_window_mask[addr];

   if (wctl & 0x20)//sprite window enabled on layer
   {
      if (wctl & 0x10)//inside or outside
      {
         if (mask == 0)
            return 0;
      }
      else
      {
         if (mask)
            return 0;
      }

      return 1;
   }
   return 3;
}