#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  interrupt_struct ;
struct TYPE_20__ {scalar_t__ numbacktrace; } ;
struct TYPE_19__ {int isinterval; int shift; scalar_t__ leftover; scalar_t__ isenable; } ;
struct TYPE_18__ {int shift; scalar_t__ leftover; } ;
struct TYPE_21__ {int delay; TYPE_3__ bt; scalar_t__ interrupts; TYPE_2__ wdt; TYPE_1__ frc; scalar_t__ isIdle; scalar_t__ cycles; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* Reset ) (TYPE_4__*) ;int /*<<< orphan*/  (* SetInterrupts ) (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* SetPR ) (TYPE_4__*,int) ;int /*<<< orphan*/  (* SetMACL ) (TYPE_4__*,int) ;int /*<<< orphan*/  (* SetMACH ) (TYPE_4__*,int) ;int /*<<< orphan*/  (* SetVBR ) (TYPE_4__*,int) ;int /*<<< orphan*/  (* SetGBR ) (TYPE_4__*,int) ;int /*<<< orphan*/  (* SetSR ) (TYPE_4__*,int) ;int /*<<< orphan*/  (* SetGPR ) (TYPE_4__*,int,int) ;} ;
typedef  TYPE_4__ SH2_struct ;

/* Variables and functions */
 int MAX_INTERRUPTS ; 
 int /*<<< orphan*/  OnchipReset (TYPE_4__*) ; 
 TYPE_15__* SH2Core ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub9 (TYPE_4__*) ; 

void SH2Reset(SH2_struct *context)
{
   int i;
   
   // Reset general registers
   for (i = 0; i < 15; i++)
      SH2Core->SetGPR(context, i, 0x00000000);

   SH2Core->SetSR(context, 0x000000F0);
   SH2Core->SetGBR(context, 0x00000000);
   SH2Core->SetVBR(context, 0x00000000);
   SH2Core->SetMACH(context, 0x00000000);
   SH2Core->SetMACL(context, 0x00000000);
   SH2Core->SetPR(context, 0x00000000);

   // Internal variables
   context->delay = 0x00000000;
   context->cycles = 0;
   context->isIdle = 0;

   context->frc.leftover = 0;
   context->frc.shift = 3;
 
   context->wdt.isenable = 0;
   context->wdt.isinterval = 1;
   context->wdt.shift = 1;
   context->wdt.leftover = 0;

   // Reset Interrupts
   memset((void *)context->interrupts, 0, sizeof(interrupt_struct) * MAX_INTERRUPTS);
   SH2Core->SetInterrupts(context, 0, context->interrupts);

   // Core specific reset
   SH2Core->Reset(context);

   // Reset Onchip modules
   OnchipReset(context);

   // Reset backtrace
   context->bt.numbacktrace = 0;
}