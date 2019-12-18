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
struct mem_ctl_info {int (* set_sdram_scrub_rate ) (struct mem_ctl_info*,unsigned long) ;} ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long) ; 
 scalar_t__ strict_strtoul (char const*,int,unsigned long*) ; 
 int stub1 (struct mem_ctl_info*,unsigned long) ; 

__attribute__((used)) static ssize_t mci_sdram_scrub_rate_store(struct mem_ctl_info *mci,
					  const char *data, size_t count)
{
	unsigned long bandwidth = 0;
	int new_bw = 0;

	if (!mci->set_sdram_scrub_rate)
		return -EINVAL;

	if (strict_strtoul(data, 10, &bandwidth) < 0)
		return -EINVAL;

	new_bw = mci->set_sdram_scrub_rate(mci, bandwidth);
	if (new_bw < 0) {
		edac_printk(KERN_WARNING, EDAC_MC,
			    "Error setting scrub rate to: %lu\n", bandwidth);
		return -EINVAL;
	}

	return count;
}