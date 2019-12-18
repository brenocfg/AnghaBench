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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long uint32_t ;
typedef  int kpc_config_t ;

/* Variables and functions */
 unsigned long long IA32_PMCx (unsigned long long) ; 
 unsigned long long kpc_configurable_count () ; 
 int /*<<< orphan*/  wrIA32_PERFEVTSELx (unsigned long long,int) ; 
 int /*<<< orphan*/  wrIA32_PMCx (unsigned long long,unsigned long long) ; 

__attribute__((used)) static int
kpc_set_configurable_config(kpc_config_t *configv, uint64_t pmc_mask)
{
	uint32_t cfg_count = kpc_configurable_count();
	uint64_t save;

	for (uint32_t i = 0; i < cfg_count; i++ ) {
		if (((1ULL << i) & pmc_mask) == 0)
			continue;

		/* need to save and restore counter since it resets when reconfigured */
		save = IA32_PMCx(i);

		/*
		 * Some bits are not safe to set from user space.
		 * Allow these bits to be set:
		 *
		 *   0-7    Event select
		 *   8-15   UMASK
		 *   16     USR
		 *   17     OS
		 *   18     E
		 *   22     EN
		 *   23     INV
		 *   24-31  CMASK
		 *
		 * Excluding:
		 *
		 *   19     PC
		 *   20     INT
		 *   21     AnyThread
		 *   32     IN_TX
		 *   33     IN_TXCP
		 *   34-63  Reserved
		 */
		wrIA32_PERFEVTSELx(i, *configv & 0xffc7ffffull);
		wrIA32_PMCx(i, save);

		/* next configuration word */
		configv++;
	}

	return 0;
}