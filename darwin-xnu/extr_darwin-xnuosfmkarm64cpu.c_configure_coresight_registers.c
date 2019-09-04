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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__* coresight_base; scalar_t__ cpu_regmap_paddr; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_DBG_LOCK_ACCESS_KEY ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGLAR ; 
 int CORESIGHT_CTI ; 
 int CORESIGHT_ED ; 
 scalar_t__ CORESIGHT_OFFSET (int) ; 
 int CORESIGHT_REGIONS ; 
 int /*<<< orphan*/  CORESIGHT_SIZE ; 
 int CORESIGHT_UTT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  coresight_debug_enabled ; 
 scalar_t__ ml_io_map (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
configure_coresight_registers(cpu_data_t *cdp)
{
	uint64_t	addr;
	int		i;

	assert(cdp);

	/*
	 * ARMv8 coresight registers are optional. If the device tree did not
	 * provide cpu_regmap_paddr, assume that coresight registers are not
	 * supported.
	 */
	if (cdp->cpu_regmap_paddr) {
		for (i = 0; i < CORESIGHT_REGIONS; ++i) {
			/* Skip CTI; these registers are debug-only (they are
			 * not present on production hardware), and there is
			 * at least one known Cyclone errata involving CTI
			 * (rdar://12802966).  We have no known clients that
			 * need the kernel to unlock CTI, so it is safer
			 * to avoid doing the access.
			 */
			if (i == CORESIGHT_CTI)
				continue;
			/* Skip debug-only registers on production chips */
			if (((i == CORESIGHT_ED) || (i == CORESIGHT_UTT)) && !coresight_debug_enabled)
				continue;

			if (!cdp->coresight_base[i]) {
				addr = cdp->cpu_regmap_paddr + CORESIGHT_OFFSET(i);
				cdp->coresight_base[i] = (vm_offset_t)ml_io_map(addr, CORESIGHT_SIZE);

				/*
				 * At this point, failing to io map the
				 * registers is considered as an error.
				 */
				if (!cdp->coresight_base[i]) {
					panic("unable to ml_io_map coresight regions");
				}
			}
			/* Unlock EDLAR, CTILAR, PMLAR */
			if (i != CORESIGHT_UTT)
				*(volatile uint32_t *)(cdp->coresight_base[i] + ARM_DEBUG_OFFSET_DBGLAR) = ARM_DBG_LOCK_ACCESS_KEY;
		}
	}
}