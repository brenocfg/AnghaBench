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
 scalar_t__ MTU_BGLR (int /*<<< orphan*/ ) ; 
 scalar_t__ MTU_CR (int /*<<< orphan*/ ) ; 
 int MTU_CRn_32BITS ; 
 int MTU_CRn_ENA ; 
 int MTU_CRn_PERIODIC ; 
 int MTU_CRn_PRESCALE_1 ; 
 scalar_t__ MTU_LR (int /*<<< orphan*/ ) ; 
 scalar_t__ mtu_base ; 
 int nmdk_cycle ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void nmdk_timer_reset(void)
{
	u32 cr;

	writel(0, mtu_base + MTU_CR(0)); /* off */

	/* configure load and background-load, and fire it up */
	writel(nmdk_cycle, mtu_base + MTU_LR(0));
	writel(nmdk_cycle, mtu_base + MTU_BGLR(0));
	cr = MTU_CRn_PERIODIC | MTU_CRn_PRESCALE_1 | MTU_CRn_32BITS;
	writel(cr, mtu_base + MTU_CR(0));
	writel(cr | MTU_CRn_ENA, mtu_base + MTU_CR(0));
}