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
struct TYPE_4__ {int intback; int intbackIreg0; int firstPeri; } ;
struct TYPE_3__ {int SF; int* IREG; int SR; int* OREG; } ;

/* Variables and functions */
 int /*<<< orphan*/  ScuSendSystemManager () ; 
 int /*<<< orphan*/  SmpcINTBACKPeripheral () ; 
 int /*<<< orphan*/  SmpcINTBACKStatus () ; 
 TYPE_2__* SmpcInternalVars ; 
 TYPE_1__* SmpcRegs ; 

__attribute__((used)) static void SmpcINTBACK(void) {
   SmpcRegs->SF = 1;

   if (SmpcInternalVars->intback) {
      SmpcINTBACKPeripheral();
      ScuSendSystemManager();
      return;
   }

   //we think rayman sets 0x40 so that it breaks the intback command immediately when it blocks,
   //rather than having to set 0x40 in response to an interrupt
   if ((SmpcInternalVars->intbackIreg0 = (SmpcRegs->IREG[0] & 1))) {
      // Return non-peripheral data
      SmpcInternalVars->firstPeri = 1;
      SmpcInternalVars->intback = (SmpcRegs->IREG[1] & 0x8) >> 3; // does the program want peripheral data too?
      SmpcINTBACKStatus();
      SmpcRegs->SR = 0x4F | (SmpcInternalVars->intback << 5); // the low nibble is undefined(or 0xF)
      ScuSendSystemManager();
      return;
   }
   if (SmpcRegs->IREG[1] & 0x8) {
      SmpcInternalVars->firstPeri = 1;
      SmpcInternalVars->intback = 1;
      SmpcRegs->SR = 0x40;
      SmpcINTBACKPeripheral();
      SmpcRegs->OREG[31] = 0x10; // may need to be changed
      ScuSendSystemManager();
      return;
   }
}