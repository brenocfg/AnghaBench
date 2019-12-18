#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int addr; } ;
typedef  TYPE_2__ memorybreakpoint_struct ;
struct TYPE_7__ {TYPE_2__* memorybreakpoint; } ;
struct TYPE_9__ {TYPE_1__ bp; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */
 int MAX_BREAKPOINTS ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static void SH2SortMemoryBreakpoints(SH2_struct *context) {
   int i, i2;
   memorybreakpoint_struct tmp;

   for (i = 0; i < (MAX_BREAKPOINTS-1); i++)
   {
      for (i2 = i+1; i2 < MAX_BREAKPOINTS; i2++)
      {
         if (context->bp.memorybreakpoint[i].addr == 0xFFFFFFFF &&
             context->bp.memorybreakpoint[i2].addr != 0xFFFFFFFF)
         {
            memcpy(&tmp, context->bp.memorybreakpoint+i, sizeof(memorybreakpoint_struct));
            memcpy(context->bp.memorybreakpoint+i, context->bp.memorybreakpoint+i2, sizeof(memorybreakpoint_struct));
            memcpy(context->bp.memorybreakpoint+i2, &tmp, sizeof(memorybreakpoint_struct));
         }
      }
   }
}