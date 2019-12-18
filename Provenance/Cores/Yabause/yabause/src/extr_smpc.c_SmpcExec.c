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
typedef  scalar_t__ s32 ;
struct TYPE_6__ {int timing; } ;
struct TYPE_5__ {int COMREG; scalar_t__ SF; } ;
struct TYPE_4__ {int LineCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMPCLOG (char*,...) ; 
 int /*<<< orphan*/  SmpcCKCHG320 () ; 
 int /*<<< orphan*/  SmpcCKCHG352 () ; 
 int /*<<< orphan*/  SmpcINTBACK () ; 
 TYPE_3__* SmpcInternalVars ; 
 int /*<<< orphan*/  SmpcNMIREQ () ; 
 int /*<<< orphan*/  SmpcRESDISA () ; 
 int /*<<< orphan*/  SmpcRESENAB () ; 
 TYPE_2__* SmpcRegs ; 
 int /*<<< orphan*/  SmpcSETSMEM () ; 
 int /*<<< orphan*/  SmpcSNDOFF () ; 
 int /*<<< orphan*/  SmpcSNDON () ; 
 int /*<<< orphan*/  SmpcSSHOFF () ; 
 int /*<<< orphan*/  SmpcSSHON () ; 
 scalar_t__ intback_wait_for_line ; 
 TYPE_1__ yabsys ; 

void SmpcExec(s32 t) {
   if (SmpcInternalVars->timing > 0) {

      if (intback_wait_for_line)
      {
         if (yabsys.LineCount == 207)
         {
            SmpcInternalVars->timing = -1;
            intback_wait_for_line = 0;
         }
      }
      SmpcInternalVars->timing -= t;
      if (SmpcInternalVars->timing <= 0) {
         switch(SmpcRegs->COMREG) {
            case 0x0:
               SMPCLOG("smpc\t: MSHON not implemented\n");
               break;
            case 0x2:
               SMPCLOG("smpc\t: SSHON\n");
               SmpcSSHON();
               break;
            case 0x3:
               SMPCLOG("smpc\t: SSHOFF\n");
               SmpcSSHOFF();
               break;
            case 0x6:
               SMPCLOG("smpc\t: SNDON\n");
               SmpcSNDON();
               break;
            case 0x7:
               SMPCLOG("smpc\t: SNDOFF\n");
               SmpcSNDOFF();
               break;
            case 0x8:
               SMPCLOG("smpc\t: CDON not implemented\n");
               break;
            case 0x9:
               SMPCLOG("smpc\t: CDOFF not implemented\n");
               break;
            case 0xD:
               SMPCLOG("smpc\t: SYSRES not implemented\n");
               break;
            case 0xE:
               SMPCLOG("smpc\t: CKCHG352\n");
               SmpcCKCHG352();
               break;
            case 0xF:
               SMPCLOG("smpc\t: CKCHG320\n");
               SmpcCKCHG320();
               break;
            case 0x10:
               SMPCLOG("smpc\t: INTBACK\n");
               SmpcINTBACK();
               break;
            case 0x17:
               SMPCLOG("smpc\t: SETSMEM\n");
               SmpcSETSMEM();
               break;
            case 0x18:
               SMPCLOG("smpc\t: NMIREQ\n");
               SmpcNMIREQ();
               break;
            case 0x19:
               SMPCLOG("smpc\t: RESENAB\n");
               SmpcRESENAB();
               break;
            case 0x1A:
               SMPCLOG("smpc\t: RESDISA\n");
               SmpcRESDISA();
               break;
            default:
               SMPCLOG("smpc\t: Command %02X not implemented\n", SmpcRegs->COMREG);
               break;
         }

         SmpcRegs->SF = 0;
      }
   }
}