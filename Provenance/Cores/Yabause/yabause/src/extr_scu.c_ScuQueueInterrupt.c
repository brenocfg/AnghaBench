#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {scalar_t__ vector; scalar_t__ level; size_t statusbit; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ scuinterrupt_struct ;
struct TYPE_6__ {size_t NumberOfInterrupts; TYPE_1__* interrupts; } ;

/* Variables and functions */
 TYPE_4__* ScuRegs ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void ScuQueueInterrupt(u8 vector, u8 level, u16 mask, u32 statusbit)
{
   u32 i, i2;
   scuinterrupt_struct tmp;

   // Make sure interrupt doesn't already exist
   for (i = 0; i < ScuRegs->NumberOfInterrupts; i++)
   {
      if (ScuRegs->interrupts[i].vector == vector)
         return;
   }

   ScuRegs->interrupts[ScuRegs->NumberOfInterrupts].vector = vector;
   ScuRegs->interrupts[ScuRegs->NumberOfInterrupts].level = level;
   ScuRegs->interrupts[ScuRegs->NumberOfInterrupts].mask = mask;
   ScuRegs->interrupts[ScuRegs->NumberOfInterrupts].statusbit = statusbit;
   ScuRegs->NumberOfInterrupts++;

   // Sort interrupts
   for (i = 0; i < (ScuRegs->NumberOfInterrupts-1); i++)
   {
      for (i2 = i+1; i2 < ScuRegs->NumberOfInterrupts; i2++)
      {
         if (ScuRegs->interrupts[i].level > ScuRegs->interrupts[i2].level)
         {
            memcpy(&tmp, &ScuRegs->interrupts[i], sizeof(scuinterrupt_struct));
            memcpy(&ScuRegs->interrupts[i], &ScuRegs->interrupts[i2], sizeof(scuinterrupt_struct));
            memcpy(&ScuRegs->interrupts[i2], &tmp, sizeof(scuinterrupt_struct));
         }
      }
   }
}