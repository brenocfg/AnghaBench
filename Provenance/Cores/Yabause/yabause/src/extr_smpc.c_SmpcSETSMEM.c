#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * SMEM; } ;
struct TYPE_3__ {int* OREG; int /*<<< orphan*/ * IREG; } ;

/* Variables and functions */
 TYPE_2__* SmpcInternalVars ; 
 TYPE_1__* SmpcRegs ; 

__attribute__((used)) static void SmpcSETSMEM(void) {
   int i;

   for(i = 0;i < 4;i++)
      SmpcInternalVars->SMEM[i] = SmpcRegs->IREG[i];

   SmpcRegs->OREG[31] = 0x17;
}