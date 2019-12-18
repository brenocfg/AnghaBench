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
typedef  int u8 ;
typedef  unsigned int u64 ;
typedef  int u32 ;
struct cpuinfo_x86 {int x86; int x86_model; } ;
struct amd64_pvt {unsigned int top_mem; unsigned int top_mem2; int nbcap; int dhar; int online_spare; int ecc_sym_sz; int /*<<< orphan*/  dbam1; int /*<<< orphan*/  F3; int /*<<< orphan*/  dchr1; int /*<<< orphan*/  dclr1; int /*<<< orphan*/  dchr0; int /*<<< orphan*/  dclr0; int /*<<< orphan*/  dbam0; int /*<<< orphan*/  F1; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBAM0 ; 
 int /*<<< orphan*/  DBAM1 ; 
 int /*<<< orphan*/  DCHR0 ; 
 int /*<<< orphan*/  DCHR1 ; 
 int /*<<< orphan*/  DCLR0 ; 
 int /*<<< orphan*/  DCLR1 ; 
 int /*<<< orphan*/  DHAR ; 
 unsigned int DRAM_RANGES ; 
 int /*<<< orphan*/  EXT_NB_MCA_CFG ; 
 int /*<<< orphan*/  F10_ONLINE_SPARE ; 
 int /*<<< orphan*/  MSR_K8_SYSCFG ; 
 int /*<<< orphan*/  MSR_K8_TOP_MEM1 ; 
 int /*<<< orphan*/  MSR_K8_TOP_MEM2 ; 
 int /*<<< orphan*/  NBCAP ; 
 int /*<<< orphan*/  amd64_read_dct_pci_cfg (struct amd64_pvt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int /*<<< orphan*/  dct_ganging_enabled (struct amd64_pvt*) ; 
 int /*<<< orphan*/  debugf0 (char*,...) ; 
 int /*<<< orphan*/  debugf1 (char*,...) ; 
 int /*<<< orphan*/  dram_dst_node (struct amd64_pvt*,unsigned int) ; 
 scalar_t__ dram_intlv_en (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  dram_intlv_sel (struct amd64_pvt*,unsigned int) ; 
 int dram_rw (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  dump_misc_regs (struct amd64_pvt*) ; 
 int /*<<< orphan*/  get_dram_base (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  get_dram_limit (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  read_dct_base_mask (struct amd64_pvt*) ; 
 int /*<<< orphan*/  read_dram_base_limit_regs (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  read_dram_ctl_register (struct amd64_pvt*) ; 

__attribute__((used)) static void read_mc_regs(struct amd64_pvt *pvt)
{
	struct cpuinfo_x86 *c = &boot_cpu_data;
	u64 msr_val;
	u32 tmp;
	unsigned range;

	/*
	 * Retrieve TOP_MEM and TOP_MEM2; no masking off of reserved bits since
	 * those are Read-As-Zero
	 */
	rdmsrl(MSR_K8_TOP_MEM1, pvt->top_mem);
	debugf0("  TOP_MEM:  0x%016llx\n", pvt->top_mem);

	/* check first whether TOP_MEM2 is enabled */
	rdmsrl(MSR_K8_SYSCFG, msr_val);
	if (msr_val & (1U << 21)) {
		rdmsrl(MSR_K8_TOP_MEM2, pvt->top_mem2);
		debugf0("  TOP_MEM2: 0x%016llx\n", pvt->top_mem2);
	} else
		debugf0("  TOP_MEM2 disabled.\n");

	amd64_read_pci_cfg(pvt->F3, NBCAP, &pvt->nbcap);

	read_dram_ctl_register(pvt);

	for (range = 0; range < DRAM_RANGES; range++) {
		u8 rw;

		/* read settings for this DRAM range */
		read_dram_base_limit_regs(pvt, range);

		rw = dram_rw(pvt, range);
		if (!rw)
			continue;

		debugf1("  DRAM range[%d], base: 0x%016llx; limit: 0x%016llx\n",
			range,
			get_dram_base(pvt, range),
			get_dram_limit(pvt, range));

		debugf1("   IntlvEn=%s; Range access: %s%s IntlvSel=%d DstNode=%d\n",
			dram_intlv_en(pvt, range) ? "Enabled" : "Disabled",
			(rw & 0x1) ? "R" : "-",
			(rw & 0x2) ? "W" : "-",
			dram_intlv_sel(pvt, range),
			dram_dst_node(pvt, range));
	}

	read_dct_base_mask(pvt);

	amd64_read_pci_cfg(pvt->F1, DHAR, &pvt->dhar);
	amd64_read_dct_pci_cfg(pvt, DBAM0, &pvt->dbam0);

	amd64_read_pci_cfg(pvt->F3, F10_ONLINE_SPARE, &pvt->online_spare);

	amd64_read_dct_pci_cfg(pvt, DCLR0, &pvt->dclr0);
	amd64_read_dct_pci_cfg(pvt, DCHR0, &pvt->dchr0);

	if (!dct_ganging_enabled(pvt)) {
		amd64_read_dct_pci_cfg(pvt, DCLR1, &pvt->dclr1);
		amd64_read_dct_pci_cfg(pvt, DCHR1, &pvt->dchr1);
	}

	pvt->ecc_sym_sz = 4;

	if (c->x86 >= 0x10) {
		amd64_read_pci_cfg(pvt->F3, EXT_NB_MCA_CFG, &tmp);
		if (c->x86 != 0x16)
			/* F16h has only DCT0 */
			amd64_read_dct_pci_cfg(pvt, DBAM1, &pvt->dbam1);

		/* F10h, revD and later can do x8 ECC too */
		if ((c->x86 > 0x10 || c->x86_model > 7) && tmp & BIT(25))
			pvt->ecc_sym_sz = 8;
	}
	dump_misc_regs(pvt);
}