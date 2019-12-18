#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int RAMCTL; } ;
typedef  TYPE_1__ Vdp2 ;

/* Variables and functions */
 scalar_t__ CheckBanks (TYPE_1__*,int) ; 

int Rbg0CheckRam(Vdp2* regs)
{
   if (((regs->RAMCTL >> 8) & 3) == 3)//both banks are divided
   {
      //ignore delta kax if the coefficient table
      //bank is unspecified
      if (CheckBanks(regs, 1))
         return 1;
   }

   return 0;
}