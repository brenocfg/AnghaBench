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
struct mem_ctl_info {int dummy; } ;
struct i82860_error_info {int errsts2; int errsts; int eap; int /*<<< orphan*/  derrsyn; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int edac_mc_find_csrow_by_page (struct mem_ctl_info*,int) ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_mc_handle_ce_no_info (struct mem_ctl_info*,char*) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int i82860_process_error_info(struct mem_ctl_info *mci,
				struct i82860_error_info *info,
				int handle_errors)
{
	int row;

	if (!(info->errsts2 & 0x0003))
		return 0;

	if (!handle_errors)
		return 1;

	if ((info->errsts ^ info->errsts2) & 0x0003) {
		edac_mc_handle_ce_no_info(mci, "UE overwrote CE");
		info->errsts = info->errsts2;
	}

	info->eap >>= PAGE_SHIFT;
	row = edac_mc_find_csrow_by_page(mci, info->eap);

	if (info->errsts & 0x0002)
		edac_mc_handle_ue(mci, info->eap, 0, row, "i82860 UE");
	else
		edac_mc_handle_ce(mci, info->eap, 0, info->derrsyn, row, 0,
				"i82860 UE");

	return 1;
}