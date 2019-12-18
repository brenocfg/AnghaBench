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
typedef  int u32 ;
struct mem_ctl_info {struct i7300_pvt* pvt_info; } ;
struct i7300_pvt {int tolm; int mc_settings; int mc_settings_a; int* mir; int /*<<< orphan*/  pci_dev_16_1_fsb_addr_map; scalar_t__ ambase; int /*<<< orphan*/  pci_dev_16_0_fsb_ctlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMBASE ; 
 scalar_t__ IS_ECC_ENABLED (int) ; 
 scalar_t__ IS_MIRRORED (int) ; 
 scalar_t__ IS_RETRY_ENABLED (int) ; 
 scalar_t__ IS_SINGLE_MODE (int) ; 
 int MAX_MIR ; 
 int /*<<< orphan*/  MC_SETTINGS ; 
 int /*<<< orphan*/  MC_SETTINGS_A ; 
 int /*<<< orphan*/  MIR0 ; 
 int /*<<< orphan*/  MIR1 ; 
 int /*<<< orphan*/  MIR2 ; 
 int /*<<< orphan*/  TOLM ; 
 int /*<<< orphan*/  debugf0 (char*,...) ; 
 int /*<<< orphan*/  debugf2 (char*,int,...) ; 
 int /*<<< orphan*/  decode_mir (int,int*) ; 
 int i7300_init_csrows (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_dimm_size (struct i7300_pvt*) ; 

__attribute__((used)) static int i7300_get_mc_regs(struct mem_ctl_info *mci)
{
	struct i7300_pvt *pvt;
	u32 actual_tolm;
	int i, rc;

	pvt = mci->pvt_info;

	pci_read_config_dword(pvt->pci_dev_16_0_fsb_ctlr, AMBASE,
			(u32 *) &pvt->ambase);

	debugf2("AMBASE= 0x%lx\n", (long unsigned int)pvt->ambase);

	/* Get the Branch Map regs */
	pci_read_config_word(pvt->pci_dev_16_1_fsb_addr_map, TOLM, &pvt->tolm);
	pvt->tolm >>= 12;
	debugf2("TOLM (number of 256M regions) =%u (0x%x)\n", pvt->tolm,
		pvt->tolm);

	actual_tolm = (u32) ((1000l * pvt->tolm) >> (30 - 28));
	debugf2("Actual TOLM byte addr=%u.%03u GB (0x%x)\n",
		actual_tolm/1000, actual_tolm % 1000, pvt->tolm << 28);

	/* Get memory controller settings */
	pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map, MC_SETTINGS,
			     &pvt->mc_settings);
	pci_read_config_dword(pvt->pci_dev_16_1_fsb_addr_map, MC_SETTINGS_A,
			     &pvt->mc_settings_a);

	if (IS_SINGLE_MODE(pvt->mc_settings_a))
		debugf0("Memory controller operating on single mode\n");
	else
		debugf0("Memory controller operating on %s mode\n",
		IS_MIRRORED(pvt->mc_settings) ? "mirrored" : "non-mirrored");

	debugf0("Error detection is %s\n",
		IS_ECC_ENABLED(pvt->mc_settings) ? "enabled" : "disabled");
	debugf0("Retry is %s\n",
		IS_RETRY_ENABLED(pvt->mc_settings) ? "enabled" : "disabled");

	/* Get Memory Interleave Range registers */
	pci_read_config_word(pvt->pci_dev_16_1_fsb_addr_map, MIR0,
			     &pvt->mir[0]);
	pci_read_config_word(pvt->pci_dev_16_1_fsb_addr_map, MIR1,
			     &pvt->mir[1]);
	pci_read_config_word(pvt->pci_dev_16_1_fsb_addr_map, MIR2,
			     &pvt->mir[2]);

	/* Decode the MIR regs */
	for (i = 0; i < MAX_MIR; i++)
		decode_mir(i, pvt->mir);

	rc = i7300_init_csrows(mci);
	if (rc < 0)
		return rc;

	/* Go and determine the size of each DIMM and place in an
	 * orderly matrix */
	print_dimm_size(pvt);

	return 0;
}