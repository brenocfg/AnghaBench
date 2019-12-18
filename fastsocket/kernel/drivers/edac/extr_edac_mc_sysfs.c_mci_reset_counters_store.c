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
struct mem_ctl_info {int nr_csrows; int /*<<< orphan*/  start_time; struct csrow_info* csrows; scalar_t__ ce_count; scalar_t__ ue_count; scalar_t__ ce_noinfo_count; scalar_t__ ue_noinfo_count; } ;
struct csrow_info {int nr_channels; TYPE_1__* channels; scalar_t__ ce_count; scalar_t__ ue_count; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ ce_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static ssize_t mci_reset_counters_store(struct mem_ctl_info *mci,
					const char *data, size_t count)
{
	int row, chan;

	mci->ue_noinfo_count = 0;
	mci->ce_noinfo_count = 0;
	mci->ue_count = 0;
	mci->ce_count = 0;

	for (row = 0; row < mci->nr_csrows; row++) {
		struct csrow_info *ri = &mci->csrows[row];

		ri->ue_count = 0;
		ri->ce_count = 0;

		for (chan = 0; chan < ri->nr_channels; chan++)
			ri->channels[chan].ce_count = 0;
	}

	mci->start_time = jiffies;
	return count;
}