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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_6__ {int numbacktrace; int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  PC; } ;
struct TYPE_7__ {int instruction; TYPE_2__ bt; TYPE_1__ regs; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */

void SH2HandleBackTrace(SH2_struct *context)
{
   u16 inst = context->instruction;
   if ((inst & 0xF000) == 0xB000 || // BSR 
      (inst & 0xF0FF) == 0x0003 || // BSRF
      (inst & 0xF0FF) == 0x400B)   // JSR
   {
      if (context->bt.numbacktrace < sizeof(context->bt.addr)/sizeof(u32))
      {
         context->bt.addr[context->bt.numbacktrace] = context->regs.PC;
         context->bt.numbacktrace++;
      }
   }
   else if (inst == 0x000B) // RTS
   {
      if (context->bt.numbacktrace > 0)
         context->bt.numbacktrace--;
   }
}