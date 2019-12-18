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
typedef  size_t u32 ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; TYPE_1__* csrows; } ;
struct amd76x_error_info {int ecc_mode_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  first_page; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd76x_process_error_info(struct mem_ctl_info *mci,
				struct amd76x_error_info *info,
				int handle_errors)
{
	int error_found;
	u32 row;

	error_found = 0;

	/*
	 *      Check for an uncorrectable error
	 */
	if (info->ecc_mode_status & BIT(8)) {
		error_found = 1;

		if (handle_errors) {
			row = (info->ecc_mode_status >> 4) & 0xf;
			edac_mc_handle_ue(mci, mci->csrows[row].first_page, 0,
					row, mci->ctl_name);
		}
	}

	/*
	 *      Check for a correctable error
	 */
	if (info->ecc_mode_status & BIT(9)) {
		error_found = 1;

		if (handle_errors) {
			row = info->ecc_mode_status & 0xf;
			edac_mc_handle_ce(mci, mci->csrows[row].first_page, 0,
					0, row, 0, mci->ctl_name);
		}
	}

	return error_found;
}