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

/* Variables and functions */
 int /*<<< orphan*/  HPET_CFG ; 
 unsigned long HPET_CFG_ENABLE ; 
 unsigned long HPET_CFG_LEGACY ; 
 int /*<<< orphan*/  hpet_address ; 
 scalar_t__ hpet_legacy_int_enabled ; 
 unsigned long hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_virt_address ; 
 int /*<<< orphan*/  hpet_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hpet_capable () ; 

void hpet_disable(void)
{
	unsigned long cfg;

	if (!is_hpet_capable() || !hpet_address || !hpet_virt_address)
		return;

	cfg = hpet_readl(HPET_CFG);
	if (hpet_legacy_int_enabled) {
		cfg &= ~HPET_CFG_LEGACY;
		hpet_legacy_int_enabled = 0;
	}
	cfg &= ~HPET_CFG_ENABLE;
	hpet_writel(cfg, HPET_CFG);
}