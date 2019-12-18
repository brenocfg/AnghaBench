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
typedef  scalar_t__ u64 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int /*<<< orphan*/  mc_node_id; } ;

/* Variables and functions */
 int amd64_get_dram_hole_info (struct mem_ctl_info*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  debugf1 (char*,unsigned long,unsigned long,...) ; 
 scalar_t__ get_dram_base (struct amd64_pvt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 dram_addr_to_sys_addr(struct mem_ctl_info *mci, u64 dram_addr)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	u64 hole_base, hole_offset, hole_size, base, sys_addr;
	int ret = 0;

	ret = amd64_get_dram_hole_info(mci, &hole_base, &hole_offset,
				      &hole_size);
	if (!ret) {
		if ((dram_addr >= hole_base) &&
		    (dram_addr < (hole_base + hole_size))) {
			sys_addr = dram_addr + hole_offset;

			debugf1("using DHAR to translate DramAddr 0x%lx to "
				"SysAddr 0x%lx\n", (unsigned long)dram_addr,
				(unsigned long)sys_addr);

			return sys_addr;
		}
	}

	base     = get_dram_base(pvt, pvt->mc_node_id);
	sys_addr = dram_addr + base;

	/*
	 * The sys_addr we have computed up to this point is a 40-bit value
	 * because the k8 deals with 40-bit values.  However, the value we are
	 * supposed to return is a full 64-bit physical address.  The AMD
	 * x86-64 architecture specifies that the most significant implemented
	 * address bit through bit 63 of a physical address must be either all
	 * 0s or all 1s.  Therefore we sign-extend the 40-bit sys_addr to a
	 * 64-bit value below.  See section 3.4.2 of AMD publication 24592:
	 * AMD x86-64 Architecture Programmer's Manual Volume 1 Application
	 * Programming.
	 */
	sys_addr |= ~((sys_addr & (1ull << 39)) - 1);

	debugf1("    Node %d, DramAddr 0x%lx to SysAddr 0x%lx\n",
		pvt->mc_node_id, (unsigned long)dram_addr,
		(unsigned long)sys_addr);

	return sys_addr;
}