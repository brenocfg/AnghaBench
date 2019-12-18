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
struct TYPE_2__ {scalar_t__ timer0; int T1MD; scalar_t__ T0C; } ;

/* Variables and functions */
 TYPE_1__* ScuRegs ; 
 int /*<<< orphan*/  ScuSendTimer0 () ; 
 int /*<<< orphan*/  SendInterrupt (int,int,int,int) ; 

void ScuSendVBlankOUT(void) {
   SendInterrupt(0x41, 0xE, 0x0002, 0x0002);
   ScuRegs->timer0 = 0;
   if (ScuRegs->T1MD & 0x1)
   {
      if (ScuRegs->timer0 == ScuRegs->T0C)
         ScuSendTimer0();
   }
}