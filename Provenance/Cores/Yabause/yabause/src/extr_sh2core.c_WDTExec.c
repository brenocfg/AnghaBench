#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_6__ {int WTCSR; int RSTCSR; int VCRWDT; int IPRA; scalar_t__ WTCNT; } ;
struct TYPE_5__ {int shift; int leftover; scalar_t__ isinterval; int /*<<< orphan*/  isenable; } ;
struct TYPE_7__ {TYPE_2__ onchip; TYPE_1__ wdt; } ;

/* Variables and functions */
 TYPE_3__* CurrentSH2 ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  SH2SendInterrupt (TYPE_3__*,int,int) ; 

void WDTExec(u32 cycles) {
   u32 wdttemp;
   u32 mask;

   if (!CurrentSH2->wdt.isenable || CurrentSH2->onchip.WTCSR & 0x80 || CurrentSH2->onchip.RSTCSR & 0x80)
      return;

   wdttemp = (u32)CurrentSH2->onchip.WTCNT;
   mask = (1 << CurrentSH2->wdt.shift) - 1;
   wdttemp += ((cycles + CurrentSH2->wdt.leftover) >> CurrentSH2->wdt.shift);
   CurrentSH2->wdt.leftover = (cycles + CurrentSH2->wdt.leftover) & mask;

   // Are we overflowing?
   if (wdttemp > 0xFF)
   {
      // Obviously depending on whether or not we're in Watchdog or Interval
      // Modes, they'll handle an overflow differently.

      if (CurrentSH2->wdt.isinterval)
      {
         // Interval Timer Mode

         // Set OVF flag
         CurrentSH2->onchip.WTCSR |= 0x80;

         // Trigger interrupt
         SH2SendInterrupt(CurrentSH2, (CurrentSH2->onchip.VCRWDT >> 8) & 0x7F, (CurrentSH2->onchip.IPRA >> 4) & 0xF);
      }
      else
      {
         // Watchdog Timer Mode(untested)
         LOG("Watchdog timer(WDT mode) overflow not implemented\n");
      }
   }

   // Write new WTCNT value
   CurrentSH2->onchip.WTCNT = (u8)wdttemp;
}