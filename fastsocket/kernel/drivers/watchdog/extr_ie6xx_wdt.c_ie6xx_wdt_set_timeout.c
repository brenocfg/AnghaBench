#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u64 ;
typedef  int u32 ;
struct watchdog_device {unsigned int timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  unlock_sequence; scalar_t__ sch_wdtba; } ;

/* Variables and functions */
 scalar_t__ PV1 ; 
 scalar_t__ PV2 ; 
 scalar_t__ RR1 ; 
 scalar_t__ WDTCR ; 
 int WDT_RELOAD ; 
 int WDT_TOUT ; 
 TYPE_1__ ie6xx_wdt_data ; 
 int /*<<< orphan*/  ie6xx_wdt_unlock_registers () ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int resetmode ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ie6xx_wdt_set_timeout(struct watchdog_device *wdd, unsigned int t)
{
	u32 preload;
	u64 clock;
	u8 wdtcr;

	/* Watchdog clock is PCI Clock (33MHz) */
	clock = 33000000;
	/* and the preload value is loaded into [34:15] of the down counter */
	preload = (t * clock) >> 15;
	/*
	 * Manual states preload must be one less.
	 * Does not wrap as t is at least 1
	 */
	preload -= 1;

	spin_lock(&ie6xx_wdt_data.unlock_sequence);

	/* Set ResetMode & Enable prescaler for range 10ms to 10 min */
	wdtcr = resetmode & 0x38;
	outb(wdtcr, ie6xx_wdt_data.sch_wdtba + WDTCR);

	ie6xx_wdt_unlock_registers();
	outl(0, ie6xx_wdt_data.sch_wdtba + PV1);

	ie6xx_wdt_unlock_registers();
	outl(preload, ie6xx_wdt_data.sch_wdtba + PV2);

	ie6xx_wdt_unlock_registers();
	outb(WDT_RELOAD | WDT_TOUT, ie6xx_wdt_data.sch_wdtba + RR1);

	spin_unlock(&ie6xx_wdt_data.unlock_sequence);

	wdd->timeout = t;
	return 0;
}