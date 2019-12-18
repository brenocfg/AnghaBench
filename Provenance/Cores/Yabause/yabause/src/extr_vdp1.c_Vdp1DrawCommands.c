#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_14__ {int addr; int EDSR; int LOPR; int COPR; } ;
typedef  TYPE_1__ Vdp1 ;
struct TYPE_13__ {int /*<<< orphan*/  (* Vdp1DrawEnd ) () ;int /*<<< orphan*/  (* Vdp1LocalCoordinate ) (int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* Vdp1SystemClipping ) (int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* Vdp1UserClipping ) (int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* Vdp1LineDraw ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Vdp1PolylineDraw ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Vdp1PolygonDraw ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Vdp1DistortedSpriteDraw ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Vdp1ScaledSpriteDraw ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Vdp1NormalSpriteDraw ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int T1ReadWord (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VDP1LOG (char*,int) ; 
 TYPE_12__* VIDCore ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void Vdp1DrawCommands(u8 * ram, Vdp1 * regs, u8* back_framebuffer)
{
   u16 command = T1ReadWord(ram, regs->addr);
   u32 commandCounter = 0;
   u32 returnAddr = 0xffffffff;

   while (!(command & 0x8000) && commandCounter < 2000) { // fix me
      // First, process the command
      if (!(command & 0x4000)) { // if (!skip)
         switch (command & 0x000F) {
         case 0: // normal sprite draw
            VIDCore->Vdp1NormalSpriteDraw(ram, regs, back_framebuffer);
            break;
         case 1: // scaled sprite draw
            VIDCore->Vdp1ScaledSpriteDraw(ram, regs, back_framebuffer);
            break;
         case 2: // distorted sprite draw
         case 3: /* this one should be invalid, but some games
                 (Hardcore 4x4 for instance) use it instead of 2 */
            VIDCore->Vdp1DistortedSpriteDraw(ram, regs, back_framebuffer);
            break;
         case 4: // polygon draw
            VIDCore->Vdp1PolygonDraw(ram, regs, back_framebuffer);
            break;
         case 5: // polyline draw
         case 7: // undocumented mirror
            VIDCore->Vdp1PolylineDraw(ram, regs, back_framebuffer);
            break;
         case 6: // line draw
            VIDCore->Vdp1LineDraw(ram, regs, back_framebuffer);
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