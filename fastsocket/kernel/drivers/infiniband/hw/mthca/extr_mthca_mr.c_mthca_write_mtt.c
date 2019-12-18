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
struct mthca_mtt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtt_buddy; int /*<<< orphan*/ * fmr_mtt_buddy; } ;
struct mthca_dev {int mthca_flags; TYPE_1__ mr_table; } ;

/* Variables and functions */
 int MTHCA_FLAG_FMR ; 
 int __mthca_write_mtt (struct mthca_dev*,struct mthca_mtt*,int,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mthca_arbel_write_mtt_seg (struct mthca_dev*,struct mthca_mtt*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_tavor_write_mtt_seg (struct mthca_dev*,struct mthca_mtt*,int,int /*<<< orphan*/ *,int) ; 
 int mthca_write_mtt_size (struct mthca_dev*) ; 

int mthca_write_mtt(struct mthca_dev *dev, struct mthca_mtt *mtt,
		    int start_index, u64 *buffer_list, int list_len)
{
	int size = mthca_write_mtt_size(dev);
	int chunk;

	if (dev->mr_table.fmr_mtt_buddy != &dev->mr_table.mtt_buddy ||
	    !(dev->mthca_flags & MTHCA_FLAG_FMR))
		return __mthca_write_mtt(dev, mtt, start_index, buffer_list, list_len);

	while (list_len > 0) {
		chunk = min(size, list_len);
		if (mthca_is_memfree(dev))
			mthca_arbel_write_mtt_seg(dev, mtt, start_index,
						  buffer_list, chunk);
		else
			mthca_tavor_write_mtt_seg(dev, mtt, start_index,
						  buffer_list, chunk);

		list_len    -= chunk;
		start_index += chunk;
		buffer_list += chunk;
	}

	return 0;
}