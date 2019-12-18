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
typedef  int u16 ;

/* Variables and functions */
 int sprintf (char*,char*) ; 

__attribute__((used)) static int setcondstr(u16 cond, char *outstring)
{
   switch (cond & 0xF)
   {
      case 0x0:
         // True
         return sprintf(outstring, "t ");
      case 0x1:
         // False
         return sprintf(outstring, "f ");
      case 0x2:
         // High
         return sprintf(outstring, "hi");
      case 0x3:
         // Low or Same
         return sprintf(outstring, "ls");
      case 0x4:
         // Carry Clear
         return sprintf(outstring, "cc");
      case 0x5:
         // Carry Set
         return sprintf(outstring, "cs");
      case 0x6:
         // Not Equal
         return sprintf(outstring, "ne");
      case 0x7:
         // Equal
         return sprintf(outstring, "eq");
      case 0x8:
         // Overflow Clear
         return sprintf(outstring, "vc");
      case 0x9:
         // Overflow Set
         return sprintf(outstring, "vs");
      case 0xA:
         // Plus
         return sprintf(outstring, "pl");
      case 0xB:
         // Minus
         return sprintf(outstring, "mi");
      case 0xC:
         // Greater or Equal
         return sprintf(outstring, "ge");
      case 0xD:
         // Less Than
         return sprintf(outstring, "lt");
      case 0xE:
         // Greater Than
         return sprintf(outstring, "gt");
      case 0xF:
         // Less or Equal
         return sprintf(outstring, "le");
      default: break;
   }

   return 0;
}