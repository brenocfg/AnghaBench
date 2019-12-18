#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  interrupt_struct ;
struct TYPE_3__ {int NumberOfInterrupts; int /*<<< orphan*/  interrupts; } ;
typedef  TYPE_1__ SH2_struct ;

/* Variables and functions */
 int MAX_INTERRUPTS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void SH2InterpreterSetInterrupts(SH2_struct *context, int num_interrupts,
                                 const interrupt_struct interrupts[MAX_INTERRUPTS])
{
   memcpy(context->interrupts, interrupts, sizeof(interrupt_struct) * MAX_INTERRUPTS);
   context->NumberOfInterrupts = num_interrupts;
}