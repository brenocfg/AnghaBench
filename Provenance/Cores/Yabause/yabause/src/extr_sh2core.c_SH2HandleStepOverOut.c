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
typedef  int u16 ;
struct TYPE_8__ {int /*<<< orphan*/  levels; scalar_t__ type; int /*<<< orphan*/  (* callBack ) (TYPE_3__*,int /*<<< orphan*/ ,void*) ;scalar_t__ enabled; int /*<<< orphan*/  address; } ;
struct TYPE_7__ {int /*<<< orphan*/  PC; int /*<<< orphan*/  PR; } ;
struct TYPE_9__ {int instruction; TYPE_2__ stepOverOut; TYPE_1__ regs; } ;
typedef  TYPE_3__ SH2_struct ;

/* Variables and functions */
#define  SH2ST_STEPOUT 129 
#define  SH2ST_STEPOVER 128 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 

void SH2HandleStepOverOut(SH2_struct *context)
{
   if (context->stepOverOut.enabled)
   {
      switch ((int)context->stepOverOut.type)
      {
      case SH2ST_STEPOVER: // Step Over
         if (context->regs.PC == context->stepOverOut.address)
         {
            context->stepOverOut.enabled = 0;
            context->stepOverOut.callBack(context, context->regs.PC, (void *)context->stepOverOut.type);
         }
         break;
      case SH2ST_STEPOUT: // Step Out
         {
            u16 inst;

            if (context->stepOverOut.levels < 0 && context->regs.PC == context->regs.PR)
            {
               context->stepOverOut.enabled = 0;
               context->stepOverOut.callBack(context, context->regs.PC, (void *)context->stepOverOut.type);
               return;
            }

            inst = context->instruction;;

            if ((inst & 0xF000) == 0xB000 || // BSR 
               (inst & 0xF0FF) == 0x0003 || // BSRF
               (inst & 0xF0FF) == 0x400B)   // JSR
               context->stepOverOut.levels++;
            else if (inst == 0x000B || // RTS
                     inst == 0x002B)   // RTE
               context->stepOverOut.levels--;

            break;
         }
      default: break;
      }
   }
}