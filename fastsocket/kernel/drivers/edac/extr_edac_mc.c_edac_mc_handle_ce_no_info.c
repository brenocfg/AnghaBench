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
struct mem_ctl_info {int /*<<< orphan*/  ce_count; int /*<<< orphan*/  ce_noinfo_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ edac_mc_get_log_ce () ; 
 int /*<<< orphan*/  edac_mc_printk (struct mem_ctl_info*,int /*<<< orphan*/ ,char*,char const*) ; 

void edac_mc_handle_ce_no_info(struct mem_ctl_info *mci, const char *msg)
{
	if (edac_mc_get_log_ce())
		edac_mc_printk(mci, KERN_WARNING,
			"CE - no information available: %s\n", msg);

	mci->ce_noinfo_count++;
	mci->ce_count++;
}