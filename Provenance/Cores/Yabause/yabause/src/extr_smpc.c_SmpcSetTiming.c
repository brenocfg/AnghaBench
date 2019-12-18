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
struct TYPE_4__ {int timing; int /*<<< orphan*/  intback; } ;
struct TYPE_3__ {int COMREG; int* IREG; int /*<<< orphan*/  SF; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMPCLOG (char*,...) ; 
 TYPE_2__* SmpcInternalVars ; 
 TYPE_1__* SmpcRegs ; 
 int intback_wait_for_line ; 

__attribute__((used)) static void SmpcSetTiming(void) {
   switch(SmpcRegs->COMREG) {
      case 0x0:
         SMPCLOG("smpc\t: MSHON not implemented\n");
         SmpcInternalVars->timing = 1;
         return;
      case 0x8:
         SMPCLOG("smpc\t: CDON not implemented\n");
         SmpcInternalVars->timing = 1;
         return;
      case 0x9:
         SMPCLOG("smpc\t: CDOFF not implemented\n");
         SmpcInternalVars->timing = 1;
         return;
      case 0xD:
      case 0xE:
      case 0xF:
         SmpcInternalVars->timing = 1; // this has to be tested on a real saturn
         return;
      case 0x10:
         if (SmpcInternalVars->intback)//continue was issued
         {
            SmpcInternalVars->timing = 16000;
            intback_wait_for_line = 1;
         }
         else {
            // Calculate timing based on what data is being retrieved

            if ((SmpcRegs->IREG[0] == 0x01) && (SmpcRegs->IREG[1] & 0x8))
            {
               //status followed by peripheral data
               SmpcInternalVars->timing = 250;
            }
            else if ((SmpcRegs->IREG[0] == 0x01) && ((SmpcRegs->IREG[1] & 0x8) == 0))
            {
               //status only
               SmpcInternalVars->timing = 250;
            }
            else if ((SmpcRegs->IREG[0] == 0) && (SmpcRegs->IREG[1] & 0x8))
            {
               //peripheral only
             SmpcInternalVars->timing = 16000;
               intback_wait_for_line = 1;
            }
         }
         return;
      case 0x17:
         SmpcInternalVars->timing = 1;
         return;
      case 0x2:
         SmpcInternalVars->timing = 1;
         return;
      case 0x3:
         SmpcInternalVars->timing = 1;
         return;
      case 0x6:
      case 0x7:
      case 0x18:
      case 0x19:
      case 0x1A:
         SmpcInternalVars->timing = 1;
         return;
      default:
         SMPCLOG("smpc\t: unimplemented command: %02X\n", SmpcRegs->COMREG);
         SmpcRegs->SF = 0;
         break;
   }
}