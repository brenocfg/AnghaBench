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
struct mem_ctl_info {int (* get_sdram_scrub_rate ) (struct mem_ctl_info*) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (struct mem_ctl_info*) ; 

__attribute__((used)) static ssize_t mci_sdram_scrub_rate_show(struct mem_ctl_info *mci, char *data)
{
	int bandwidth = 0;

	if (!mci->get_sdram_scrub_rate)
		return -EINVAL;

	bandwidth = mci->get_sdram_scrub_rate(mci);
	if (bandwidth < 0) {
		edac_printk(KERN_DEBUG, EDAC_MC, "Error reading scrub rate\n");
		return bandwidth;
	}

	return sprintf(data, "%d\n", bandwidth);
}