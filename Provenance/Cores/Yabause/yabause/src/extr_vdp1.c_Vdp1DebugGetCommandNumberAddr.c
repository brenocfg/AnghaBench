#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;

/* Variables and functions */
 int T1ReadWord (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Vdp1Ram ; 

__attribute__((used)) static u32 Vdp1DebugGetCommandNumberAddr(u32 number)
{
   u32 addr = 0;
   u32 returnAddr = 0xFFFFFFFF;
   u32 commandCounter = 0;
   u16 command;

   command = T1ReadWord(Vdp1Ram, addr);

   while (!(command & 0x8000) && commandCounter != number)
   {
      // Make sure we're still dealing with a valid command
      if ((command & 0x000C) == 0x000C)
         // Invalid, abort
         return 0xFFFFFFFF;

      // Determine where to go next
      switch ((command & 0x3000) >> 12)
      {
         case 0: // NEXT, jump to following table
            addr += 0x20;
            break;
         case 1: // ASSIGN, jump to CMDLINK
            addr = T1ReadWord(Vdp1Ram, addr + 2) * 8;
            break;
         case 2: // CALL, call a subroutine
            if (returnAddr == 0xFFFFFFFF)
               returnAddr = addr + 0x20;

            addr = T1ReadWord(Vdp1Ram, addr + 2) * 8;
            break;
         case 3: // RETURN, return from subroutine
            if (returnAddr != 0xFFFFFFFF) {
               addr = returnAddr;
               returnAddr = 0xFFFFFFFF;
            }
            else
               addr += 0x20;
            break;
      }

      if (addr > 0x7FFE0)
         return 0xFFFFFFFF;
      command = T1ReadWord(Vdp1Ram, addr);
      commandCounter++;
   }

   if (commandCounter == number)
      return addr;
   else
      return 0xFFFFFFFF;
}