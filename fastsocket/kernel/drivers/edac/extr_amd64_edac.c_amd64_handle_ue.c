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
typedef  int /*<<< orphan*/  u32 ;
struct mem_ctl_info {int dummy; } ;
struct mce {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int MCI_STATUS_ADDRV ; 
 int /*<<< orphan*/  amd64_mc_err (struct mem_ctl_info*,char*,...) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ue_no_info (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_address_to_page_and_offset (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mem_ctl_info* find_mc_by_sys_addr (struct mem_ctl_info*,scalar_t__) ; 
 scalar_t__ get_error_address (struct mce*) ; 
 int sys_addr_to_csrow (struct mem_ctl_info*,scalar_t__) ; 

__attribute__((used)) static void amd64_handle_ue(struct mem_ctl_info *mci, struct mce *m)
{
	struct mem_ctl_info *log_mci, *src_mci = NULL;
	int csrow;
	u64 sys_addr;
	u32 page, offset;

	log_mci = mci;

	if (!(m->status & MCI_STATUS_ADDRV)) {
		amd64_mc_err(mci, "HW has no ERROR_ADDRESS available\n");
		edac_mc_handle_ue_no_info(log_mci, EDAC_MOD_STR);
		return;
	}

	sys_addr = get_error_address(m);

	/*
	 * Find out which node the error address belongs to. This may be
	 * different from the node that detected the error.
	 */
	src_mci = find_mc_by_sys_addr(mci, sys_addr);
	if (!src_mci) {
		amd64_mc_err(mci, "ERROR ADDRESS (0x%lx) NOT mapped to a MC\n",
				  (unsigned long)sys_addr);
		edac_mc_handle_ue_no_info(log_mci, EDAC_MOD_STR);
		return;
	}

	log_mci = src_mci;

	csrow = sys_addr_to_csrow(log_mci, sys_addr);
	if (csrow < 0) {
		amd64_mc_err(mci, "ERROR_ADDRESS (0x%lx) NOT mapped to CS\n",
				  (unsigned long)sys_addr);
		edac_mc_handle_ue_no_info(log_mci, EDAC_MOD_STR);
	} else {
		error_address_to_page_and_offset(sys_addr, &page, &offset);
		edac_mc_handle_ue(log_mci, page, offset, csrow, EDAC_MOD_STR);
	}
}