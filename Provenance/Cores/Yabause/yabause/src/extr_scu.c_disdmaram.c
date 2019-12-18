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

__attribute__((used)) static char *disdmaram(u8 num)
{
   switch(num)
   {
      case 0x0: // MC0
         return "MC0";
      case 0x1: // MC1
         return "MC1";
      case 0x2: // MC2
         return "MC2";
      case 0x3: // MC3
         return "MC3";
      case 0x4: // Program Ram
         return "PRG";
      default: break;
   }

   return "??";
}