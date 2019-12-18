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
struct mem_ctl_info {int /*<<< orphan*/  ue_count; int /*<<< orphan*/  ue_noinfo_count; int /*<<< orphan*/  mc_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ edac_mc_get_log_ue () ; 
 scalar_t__ edac_mc_get_panic_on_ue () ; 
 int /*<<< orphan*/  edac_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

void edac_mc_handle_ue_no_info(struct mem_ctl_info *mci, const char *msg)
{
	if (edac_mc_get_panic_on_ue())
		panic("EDAC MC%d: Uncorrected Error", mci->mc_idx);

	if (edac_mc_get_log_ue())
		edac_mc_printk(mci, KERN_WARNING,
			"UE - no information available: %s\n", msg);
	mci->ue_noinfo_count++;
	mci->ue_count++;
}