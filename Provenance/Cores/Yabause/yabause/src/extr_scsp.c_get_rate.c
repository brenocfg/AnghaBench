#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int krs; int fns; int oct; } ;
struct Slot {TYPE_1__ regs; } ;
typedef  int s32 ;

/* Variables and functions */

s32 get_rate(struct Slot * slot, int rate)
{
   s32 result = 0;

   if (slot->regs.krs == 0xf)
      result = rate * 2;
   else
   {
      result = (slot->regs.krs * 2) + (rate * 2) + ((slot->regs.fns >> 9) & 1);
      result = (8 ^ slot->regs.oct) + (result - 8);
   }

   if (result <= 0)
      return 0;

   if (result >= 0x3c)
      return 0x3c;

   return result;
}