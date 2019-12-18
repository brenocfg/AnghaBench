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
typedef  unsigned long long u64 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int /*<<< orphan*/  mc_node_id; } ;

/* Variables and functions */
 unsigned long long GENMASK (int /*<<< orphan*/ ,int) ; 
 int amd64_get_dram_hole_info (struct mem_ctl_info*,unsigned long long*,unsigned long long*,unsigned long long*) ; 
 int /*<<< orphan*/  debugf2 (char*,unsigned long,unsigned long) ; 
 unsigned long long get_dram_base (struct amd64_pvt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 sys_addr_to_dram_addr(struct mem_ctl_info *mci, u64 sys_addr)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	u64 dram_base, hole_base, hole_offset, hole_size, dram_addr;
	int ret = 0;

	dram_base = get_dram_base(pvt, pvt->mc_node_id);

	ret = amd64_get_dram_hole_info(mci, &hole_base, &hole_offset,
				      &hole_size);
	if (!ret) {
		if ((sys_addr >= (1ull << 32)) &&
		    (sys_addr < ((1ull << 32) + hole_size))) {
			/* use DHAR to translate SysAddr to DramAddr */
			dram_addr = sys_addr - hole_offset;

			debugf2("using DHAR to translate SysAddr 0x%lx to "
				"DramAddr 0x%lx\n",
				(unsigned long)sys_addr,
				(unsigned long)dram_addr);

			return dram_addr;
		}
	}

	/*
	 * Translate the SysAddr to a DramAddr as shown near the start of
	 * section 3.4.4 (p. 70).  Although sys_addr is a 64-bit value, the k8
	 * only deals with 40-bit values.  Therefore we discard bits 63-40 of
	 * sys_addr below.  If bit 39 of sys_addr is 1 then the bits we
	 * discard are all 1s.  Otherwise the bits we discard are all 0s.  See
	 * section 3.4.2 of AMD publication 24592: AMD x86-64 Architecture
	 * Programmer's Manual Volume 1 Application Programming.
	 */
	dram_addr = (sys_addr & GENMASK(0, 39)) - dram_base;

	debugf2("using DRAM Base register to translate SysAddr 0x%lx to "
		"DramAddr 0x%lx\n", (unsigned long)sys_addr,
		(unsigned long)dram_addr);
	return dram_addr;
}