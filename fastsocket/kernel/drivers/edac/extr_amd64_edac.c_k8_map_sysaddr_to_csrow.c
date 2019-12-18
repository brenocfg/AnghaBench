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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct amd64_pvt {int nbcfg; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int NBCFG_CHIPKILL ; 
 int /*<<< orphan*/  amd64_mc_err (struct mem_ctl_info*,char*,unsigned long) ; 
 int /*<<< orphan*/  amd64_mc_warn (struct mem_ctl_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ce_no_info (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_address_to_page_and_offset (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mem_ctl_info* find_mc_by_sys_addr (struct mem_ctl_info*,int) ; 
 int get_channel_from_ecc_syndrome (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 
 int sys_addr_to_csrow (struct mem_ctl_info*,int) ; 

__attribute__((used)) static void k8_map_sysaddr_to_csrow(struct mem_ctl_info *mci, u64 sys_addr,
				    u16 syndrome)
{
	struct mem_ctl_info *src_mci;
	struct amd64_pvt *pvt = mci->pvt_info;
	int channel, csrow;
	u32 page, offset;

	/* CHIPKILL enabled */
	if (pvt->nbcfg & NBCFG_CHIPKILL) {
		channel = get_channel_from_ecc_syndrome(mci, syndrome);
		if (channel < 0) {
			/*
			 * Syndrome didn't map, so we don't know which of the
			 * 2 DIMMs is in error. So we need to ID 'both' of them
			 * as suspect.
			 */
			amd64_mc_warn(mci, "unknown syndrome 0x%04x - possible "
					   "error reporting race\n", syndrome);
			edac_mc_handle_ce_no_info(mci, EDAC_MOD_STR);
			return;
		}
	} else {
		/*
		 * non-chipkill ecc mode
		 *
		 * The k8 documentation is unclear about how to determine the
		 * channel number when using non-chipkill memory.  This method
		 * was obtained from email communication with someone at AMD.
		 * (Wish the email was placed in this comment - norsk)
		 */
		channel = ((sys_addr & BIT(3)) != 0);
	}

	/*
	 * Find out which node the error address belongs to. This may be
	 * different from the node that detected the error.
	 */
	src_mci = find_mc_by_sys_addr(mci, sys_addr);
	if (!src_mci) {
		amd64_mc_err(mci, "failed to map error addr 0x%lx to a node\n",
			     (unsigned long)sys_addr);
		edac_mc_handle_ce_no_info(mci, EDAC_MOD_STR);
		return;
	}

	/* Now map the sys_addr to a CSROW */
	csrow = sys_addr_to_csrow(src_mci, sys_addr);
	if (csrow < 0) {
		edac_mc_handle_ce_no_info(src_mci, EDAC_MOD_STR);
	} else {
		error_address_to_page_and_offset(sys_addr, &page, &offset);

		edac_mc_handle_ce(src_mci, page, offset, syndrome, csrow,
				  channel, EDAC_MOD_STR);
	}
}