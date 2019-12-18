#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scuinterrupt_struct ;
struct TYPE_5__ {unsigned int NumberOfInterrupts; int IMS; TYPE_1__* interrupts; int /*<<< orphan*/  IST; } ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  statusbit; int /*<<< orphan*/  level; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  SH2SendInterrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ScuRegs ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

void ScuTestInterruptMask()
{
   unsigned int i, i2;

   // Handle SCU interrupts
   for (i = 0; i < ScuRegs->NumberOfInterrupts; i++)
   {
      if (!(ScuRegs->IMS & ScuRegs->interrupts[ScuRegs->NumberOfInterrupts-1-i].mask))
      {
         SH2SendInterrupt(MSH2, ScuRegs->interrupts[ScuRegs->NumberOfInterrupts-1-i].vector, ScuRegs->interrupts[ScuRegs->NumberOfInterrupts-1-i].level);
         ScuRegs->IST &= ~ScuRegs->interrupts[ScuRegs->NumberOfInterrupts-1-i].statusbit;

         // Shorten list
         for (i2 = ScuRegs->NumberOfInterrupts-1-i; i2 < (ScuRegs->NumberOfInterrupts-1); i2++)
            memcpy(&ScuRegs->interrupts[i2], &ScuRegs->interrupts[i2+1], sizeof(scuinterrupt_struct));

         ScuRegs->NumberOfInterrupts--;
         break;
      }
   }
}