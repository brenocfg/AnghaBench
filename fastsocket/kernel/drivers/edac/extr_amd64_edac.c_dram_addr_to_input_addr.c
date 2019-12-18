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
typedef  int u64 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int dummy; } ;

/* Variables and functions */
 int GENMASK (int,int) ; 
 int /*<<< orphan*/  debugf2 (char*,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dram_intlv_en (struct amd64_pvt*,int /*<<< orphan*/ ) ; 
 int num_node_interleave_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 dram_addr_to_input_addr(struct mem_ctl_info *mci, u64 dram_addr)
{
	struct amd64_pvt *pvt;
	int intlv_shift;
	u64 input_addr;

	pvt = mci->pvt_info;

	/*
	 * See the start of section 3.4.4 (p. 70, BKDG #26094, K8, revA-E)
	 * concerning translating a DramAddr to an InputAddr.
	 */
	intlv_shift = num_node_interleave_bits(dram_intlv_en(pvt, 0));
	input_addr = ((dram_addr >> intlv_shift) & GENMASK(12, 35)) +
		      (dram_addr & 0xfff);

	debugf2("  Intlv Shift=%d DramAddr=0x%lx maps to InputAddr=0x%lx\n",
		intlv_shift, (unsigned long)dram_addr,
		(unsigned long)input_addr);

	return input_addr;
}