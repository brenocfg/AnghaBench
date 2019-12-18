#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scuinterrupt_struct ;
struct TYPE_4__ {scalar_t__ all; } ;
struct TYPE_6__ {TYPE_1__ ProgControlPort; } ;
struct TYPE_5__ {int D0AD; int D1AD; int D2AD; int D0EN; int D1EN; int D2EN; int D0MD; int D1MD; int D2MD; int DSTP; int DSTA; int PDA; int T1MD; int IMS; int IST; int AIACK; int ASR0; int ASR1; int AREF; int RSEL; int VER; scalar_t__ NumberOfInterrupts; scalar_t__ interrupts; scalar_t__ timer1; scalar_t__ timer0; } ;

/* Variables and functions */
 TYPE_3__* ScuDsp ; 
 TYPE_2__* ScuRegs ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void ScuReset(void) {
   ScuRegs->D0AD = ScuRegs->D1AD = ScuRegs->D2AD = 0x101;
   ScuRegs->D0EN = ScuRegs->D1EN = ScuRegs->D2EN = 0x0;
   ScuRegs->D0MD = ScuRegs->D1MD = ScuRegs->D2MD = 0x7;
   ScuRegs->DSTP = 0x0;
   ScuRegs->DSTA = 0x0;

   ScuDsp->ProgControlPort.all = 0;
   ScuRegs->PDA = 0x0;

   ScuRegs->T1MD = 0x0;

   ScuRegs->IMS = 0xBFFF;
   ScuRegs->IST = 0x0;

   ScuRegs->AIACK = 0x0;
   ScuRegs->ASR0 = ScuRegs->ASR1 = 0x0;
   ScuRegs->AREF = 0x0;

   ScuRegs->RSEL = 0x0;
   ScuRegs->VER = 0x04; // Looks like all consumer saturn's used at least version 4

   ScuRegs->timer0 = 0;
   ScuRegs->timer1 = 0;

   memset((void *)ScuRegs->interrupts, 0, sizeof(scuinterrupt_struct) * 30);
   ScuRegs->NumberOfInterrupts = 0;
}