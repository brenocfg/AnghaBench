#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_7__ {int addr; int EDSR; int LOPR; int COPR; } ;
typedef  TYPE_1__ Vdp1 ;
struct TYPE_8__ {int /*<<< orphan*/  (* Vdp1DrawEnd ) () ;int /*<<< orphan*/  (* Vdp1LocalCoordinate ) (int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* Vdp1SystemClipping ) (int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* Vdp1UserClipping ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;

/* Variables and functions */
 int T1ReadWord (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VDP1LOG (char*,int) ; 
 TYPE_6__* VIDCore ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub4 () ; 

void Vdp1FakeDrawCommands(u8 * ram, Vdp1 * regs)
{
   u16 command = T1ReadWord(ram, regs->addr);
   u32 commandCounter = 0;
   u32 returnAddr = 0xffffffff;

   while (!(command & 0x8000) && commandCounter < 2000) { // fix me
      // First, process the command
      if (!(command & 0x4000)) { // if (!skip)
         switch (command & 0x000F) {
         case 0: // normal sprite draw
         case 1: // scaled sprite draw
         case 2: // distorted sprite draw
         case 3: /* this one should be invalid, but some games
                 (Hardcore 4x4 for instance) use it instead of 2 */
         case 4: // polygon draw
         case 5: // polyline draw
         case 6: // line draw
         case 7: // undocumented polyline draw mirror
            break;
         case 8: // user clipping coordinates
         case 11: // undocumented mirror
            VIDCore->Vdp1UserClipping(ram, regs);
            break;
         case 9: // system clipping coordinates
            VIDCore->Vdp1SystemClipping(ram, regs);
            break;
         case 10: // local coordinate
            VIDCore->Vdp1LocalCoordinate(ram, regs);
            break;
         default: // Abort
            VDP1LOG("vdp1\t: Bad command: %x\n", command);
            regs->EDSR |= 2;
            VIDCore->Vdp1DrawEnd();
            regs->LOPR = regs->addr >> 3;
            regs->COPR = regs->addr >> 3;
            return;
         }
      }

      // Next, determine where to go next
      switch ((command & 0x3000) >> 12) {
      case 0: // NEXT, jump to following table
         regs->addr += 0x20;
         break;
      case 1: // ASSIGN, jump to CMDLINK
         regs->addr = T1ReadWord(ram, regs->addr + 2) * 8;
         break;
      case 2: // CALL, call a subroutine
         if (returnAddr == 0xFFFFFFFF)
            returnAddr = regs->addr + 0x20;

         regs->addr = T1ReadWord(ram, regs->addr + 2) * 8;
         break;
      case 3: // RETURN, return from subroutine
         if (returnAddr != 0xFFFFFFFF) {
            regs->addr = returnAddr;
            returnAddr = 0xFFFFFFFF;
         }
         else
            regs->addr += 0x20;
         break;
      }

      command = T1ReadWord(ram, regs->addr);
      commandCounter++;
   }
}