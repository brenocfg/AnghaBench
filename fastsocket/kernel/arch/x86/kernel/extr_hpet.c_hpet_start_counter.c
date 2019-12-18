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
 unsigned long hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpet_start_counter(void)
{
	unsigned long cfg = hpet_readl(HPET_CFG);
	cfg |= HPET_CFG_ENABLE;
	hpet_writel(cfg, HPET_CFG);
}