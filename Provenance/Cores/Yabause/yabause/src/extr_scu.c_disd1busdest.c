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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static char *disd1busdest(u8 num)
{
   switch(num) { 
      case 0x0:
         return "MC0";
      case 0x1:
         return "MC1";
      case 0x2:
         return "MC2";
      case 0x3:
         return "MC3";
      case 0x4:
         return "RX";
      case 0x5:
         return "PL";
      case 0x6:
         return "RA0";
      case 0x7:
         return "WA0";
      case 0xA:
         return "LOP";
      case 0xB:
         return "TOP";
      case 0xC:
         return "CT0";
      case 0xD:
         return "CT1";
      case 0xE:
         return "CT2";
      case 0xF:
         return "CT3";
      default: break;
   }

   return "??";
}