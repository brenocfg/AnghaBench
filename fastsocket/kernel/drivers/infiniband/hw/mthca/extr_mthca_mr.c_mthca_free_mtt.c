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
struct mthca_mtt {int order; scalar_t__ first_seg; int /*<<< orphan*/  buddy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtt_table; } ;
struct mthca_dev {TYPE_1__ mr_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mthca_mtt*) ; 
 int /*<<< orphan*/  mthca_buddy_free (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mthca_table_put_range (struct mthca_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void mthca_free_mtt(struct mthca_dev *dev, struct mthca_mtt *mtt)
{
	if (!mtt)
		return;

	mthca_buddy_free(mtt->buddy, mtt->first_seg, mtt->order);

	mthca_table_put_range(dev, dev->mr_table.mtt_table,
			      mtt->first_seg,
			      mtt->first_seg + (1 << mtt->order) - 1);

	kfree(mtt);
}