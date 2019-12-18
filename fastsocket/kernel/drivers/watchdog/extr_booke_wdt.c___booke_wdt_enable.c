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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_TCR ; 
 int TCR_WIE ; 
 int TCR_WRC (int /*<<< orphan*/ ) ; 
 int WDTP (int /*<<< orphan*/ ) ; 
 int WDTP_MASK ; 
 int /*<<< orphan*/  WRC_CHIP ; 
 int /*<<< orphan*/  __booke_wdt_ping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  booke_wdt_period ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __booke_wdt_enable(void *data)
{
	u32 val;

	/* clear status before enabling watchdog */
	__booke_wdt_ping(NULL);
	val = mfspr(SPRN_TCR);
	val &= ~WDTP_MASK;
	val |= (TCR_WIE|TCR_WRC(WRC_CHIP)|WDTP(booke_wdt_period));

	mtspr(SPRN_TCR, val);
}