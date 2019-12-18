#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int nummemorybreakpoints; TYPE_1__* memorybreakpoint; } ;
struct TYPE_7__ {TYPE_2__ bp; } ;
struct TYPE_5__ {int addr; int flags; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */

__attribute__((used)) static int CheckForMemoryBreakpointDupes(SH2_struct *context, u32 addr, u32 flag, int *which)
{
   int i;

   for (i = 0; i < context->bp.nummemorybreakpoints; i++)
   {
      if (((context->bp.memorybreakpoint[i].addr >> 16) & 0xFFF) ==
          ((addr >> 16) & 0xFFF))
      {
         // See it actually was using the same operation flag
         if (context->bp.memorybreakpoint[i].flags & flag)
         {
            *which = i;
            return 1;
         }
      }                
   }

   return 0;
}