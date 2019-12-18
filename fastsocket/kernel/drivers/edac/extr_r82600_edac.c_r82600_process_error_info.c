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
struct r82600_error_info {int eapr; } ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; } ;

/* Variables and functions */
 int BIT (int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_find_csrow_by_page (struct mem_ctl_info*,int) ; 
 int /*<<< orphan*/  edac_mc_handle_ce (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_handle_ue (struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r82600_process_error_info(struct mem_ctl_info *mci,
				struct r82600_error_info *info,
				int handle_errors)
{
	int error_found;
	u32 eapaddr, page;
	u32 syndrome;

	error_found = 0;

	/* bits 30:12 store the upper 19 bits of the 32 bit error address */
	eapaddr = ((info->eapr >> 12) & 0x7FFF) << 13;
	/* Syndrome in bits 11:4 [p.62]       */
	syndrome = (info->eapr >> 4) & 0xFF;

	/* the R82600 reports at less than page *
	 * granularity (upper 19 bits only)     */
	page = eapaddr >> PAGE_SHIFT;

	if (info->eapr & BIT(0)) {	/* CE? */
		error_found = 1;

		if (handle_errors)
			edac_mc_handle_ce(mci, page, 0,	/* not avail */
					syndrome,
					edac_mc_find_csrow_by_page(mci, page),
					0, mci->ctl_name);
	}

	if (info->eapr & BIT(1)) {	/* UE? */
		error_found = 1;

		if (handle_errors)
			/* 82600 doesn't give enough info */
			edac_mc_handle_ue(mci, page, 0,
					edac_mc_find_csrow_by_page(mci, page),
					mci->ctl_name);
	}

	return error_found;
}