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
struct amd64_pvt {char* dct_sel_lo; char* dct_sel_hi; } ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCT_SEL_HI ; 
 int /*<<< orphan*/  DCT_SEL_LO ; 
 int /*<<< orphan*/  amd64_read_dct_pci_cfg (struct amd64_pvt*,int /*<<< orphan*/ ,char**) ; 
 TYPE_1__ boot_cpu_data ; 
 scalar_t__ dct_data_intlv_enabled (struct amd64_pvt*) ; 
 scalar_t__ dct_ganging_enabled (struct amd64_pvt*) ; 
 scalar_t__ dct_high_range_enabled (struct amd64_pvt*) ; 
 scalar_t__ dct_interleave_enabled (struct amd64_pvt*) ; 
 scalar_t__ dct_memory_cleared (struct amd64_pvt*) ; 
 char* dct_sel_baseaddr (struct amd64_pvt*) ; 
 char* dct_sel_interleave_addr (struct amd64_pvt*) ; 
 int /*<<< orphan*/  debugf0 (char*,char*,...) ; 

__attribute__((used)) static void read_dram_ctl_register(struct amd64_pvt *pvt)
{

	if (boot_cpu_data.x86 == 0xf)
		return;

	if (!amd64_read_dct_pci_cfg(pvt, DCT_SEL_LO, &pvt->dct_sel_lo)) {
		debugf0("F2x110 (DCTSelLow): 0x%08x, High range addrs at: 0x%x\n",
			pvt->dct_sel_lo, dct_sel_baseaddr(pvt));

		debugf0("  DCTs operate in %s mode.\n",
			(dct_ganging_enabled(pvt) ? "ganged" : "unganged"));

		if (!dct_ganging_enabled(pvt))
			debugf0("  Address range split per DCT: %s\n",
				(dct_high_range_enabled(pvt) ? "yes" : "no"));

		debugf0("  data interleave for ECC: %s, "
			"DRAM cleared since last warm reset: %s\n",
			(dct_data_intlv_enabled(pvt) ? "enabled" : "disabled"),
			(dct_memory_cleared(pvt) ? "yes" : "no"));

		debugf0("  channel interleave: %s, "
			"interleave bits selector: 0x%x\n",
			(dct_interleave_enabled(pvt) ? "enabled" : "disabled"),
			dct_sel_interleave_addr(pvt));
	}

	amd64_read_dct_pci_cfg(pvt, DCT_SEL_HI, &pvt->dct_sel_hi);
}