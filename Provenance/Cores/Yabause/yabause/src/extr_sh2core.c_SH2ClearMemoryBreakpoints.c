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
struct TYPE_6__ {scalar_t__ nummemorybreakpoints; TYPE_1__* memorybreakpoint; } ;
struct TYPE_7__ {TYPE_2__ bp; } ;
struct TYPE_5__ {int addr; int /*<<< orphan*/ * oldwritelong; int /*<<< orphan*/ * oldwriteword; int /*<<< orphan*/ * oldwritebyte; int /*<<< orphan*/ * oldreadlong; int /*<<< orphan*/ * oldreadword; int /*<<< orphan*/ * oldreadbyte; scalar_t__ flags; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */
 int MAX_BREAKPOINTS ; 

void SH2ClearMemoryBreakpoints(SH2_struct *context) {
   int i;
   for (i = 0; i < MAX_BREAKPOINTS; i++)
   {
      context->bp.memorybreakpoint[i].addr = 0xFFFFFFFF;
      context->bp.memorybreakpoint[i].flags = 0;
      context->bp.memorybreakpoint[i].oldreadbyte = NULL;
      context->bp.memorybreakpoint[i].oldreadword = NULL;
      context->bp.memorybreakpoint[i].oldreadlong = NULL;
      context->bp.memorybreakpoint[i].oldwritebyte = NULL;
      context->bp.memorybreakpoint[i].oldwriteword = NULL;
      context->bp.memorybreakpoint[i].oldwritelong = NULL;
   }
   context->bp.nummemorybreakpoints = 0;
}