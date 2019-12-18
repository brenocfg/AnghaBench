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
 scalar_t__ BCMCPU_IS_6338 () ; 
 scalar_t__ BCMCPU_IS_6345 () ; 
 scalar_t__ BCMCPU_IS_6348 () ; 
 scalar_t__ BCMCPU_IS_6358 () ; 
 int /*<<< orphan*/  DDR_DMIPSPLLCFG_REG ; 
 unsigned int DMIPSPLLCFG_M1_MASK ; 
 unsigned int DMIPSPLLCFG_M1_SHIFT ; 
 unsigned int DMIPSPLLCFG_N1_MASK ; 
 unsigned int DMIPSPLLCFG_N1_SHIFT ; 
 unsigned int DMIPSPLLCFG_N2_MASK ; 
 unsigned int DMIPSPLLCFG_N2_SHIFT ; 
 unsigned int MIPSPLLCTL_M1CPU_MASK ; 
 unsigned int MIPSPLLCTL_M1CPU_SHIFT ; 
 unsigned int MIPSPLLCTL_N1_MASK ; 
 unsigned int MIPSPLLCTL_N1_SHIFT ; 
 unsigned int MIPSPLLCTL_N2_MASK ; 
 unsigned int MIPSPLLCTL_N2_SHIFT ; 
 int /*<<< orphan*/  PERF_MIPSPLLCTL_REG ; 
 unsigned int bcm_ddr_readl (int /*<<< orphan*/ ) ; 
 unsigned int bcm_perf_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int detect_cpu_clock(void)
{
	unsigned int tmp, n1 = 0, n2 = 0, m1 = 0;

	/* BCM6338 has a fixed 240 Mhz frequency */
	if (BCMCPU_IS_6338())
		return 240000000;

	/* BCM6345 has a fixed 140Mhz frequency */
	if (BCMCPU_IS_6345())
		return 140000000;

	/*
	 * frequency depends on PLL configuration:
	 */
	if (BCMCPU_IS_6348()) {
		/* 16MHz * (N1 + 1) * (N2 + 2) / (M1_CPU + 1) */
		tmp = bcm_perf_readl(PERF_MIPSPLLCTL_REG);
		n1 = (tmp & MIPSPLLCTL_N1_MASK) >> MIPSPLLCTL_N1_SHIFT;
		n2 = (tmp & MIPSPLLCTL_N2_MASK) >> MIPSPLLCTL_N2_SHIFT;
		m1 = (tmp & MIPSPLLCTL_M1CPU_MASK) >> MIPSPLLCTL_M1CPU_SHIFT;
		n1 += 1;
		n2 += 2;
		m1 += 1;
	}

	if (BCMCPU_IS_6358()) {
		/* 16MHz * N1 * N2 / M1_CPU */
		tmp = bcm_ddr_readl(DDR_DMIPSPLLCFG_REG);
		n1 = (tmp & DMIPSPLLCFG_N1_MASK) >> DMIPSPLLCFG_N1_SHIFT;
		n2 = (tmp & DMIPSPLLCFG_N2_MASK) >> DMIPSPLLCFG_N2_SHIFT;
		m1 = (tmp & DMIPSPLLCFG_M1_MASK) >> DMIPSPLLCFG_M1_SHIFT;
	}

	return (16 * 1000000 * n1 * n2) / m1;
}