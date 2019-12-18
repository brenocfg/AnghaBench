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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct mce {int status; } ;
struct amd64_pvt {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* map_sysaddr_to_csrow ) (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int MCI_STATUS_ADDRV ; 
 int /*<<< orphan*/  amd64_mc_err (struct mem_ctl_info*,char*,...) ; 
 int /*<<< orphan*/  edac_mc_handle_ce_no_info (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_syndrome (int) ; 
 int /*<<< orphan*/  get_error_address (struct mce*) ; 
 int /*<<< orphan*/  stub1 (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd64_handle_ce(struct mem_ctl_info *mci, struct mce *m)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	u64 sys_addr;
	u16 syndrome;

	/* Ensure that the Error Address is VALID */
	if (!(m->status & MCI_STATUS_ADDRV)) {
		amd64_mc_err(mci, "HW has no ERROR_ADDRESS available\n");
		edac_mc_handle_ce_no_info(mci, EDAC_MOD_STR);
		return;
	}

	sys_addr = get_error_address(m);
	syndrome = extract_syndrome(m->status);

	amd64_mc_err(mci, "CE ERROR_ADDRESS= 0x%llx\n", sys_addr);

	pvt->ops->map_sysaddr_to_csrow(mci, sys_addr, syndrome);
}