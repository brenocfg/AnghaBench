#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lkey; } ;
struct mthca_mr {int /*<<< orphan*/  mtt; TYPE_2__ ibmr; } ;
struct TYPE_3__ {int num_mpts; } ;
struct mthca_dev {TYPE_1__ limits; } ;

/* Variables and functions */
 int key_to_hw_index (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_HW2SW_MPT (struct mthca_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mthca_free_mtt (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_region (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int) ; 

void mthca_free_mr(struct mthca_dev *dev, struct mthca_mr *mr)
{
	int err;

	err = mthca_HW2SW_MPT(dev, NULL,
			      key_to_hw_index(dev, mr->ibmr.lkey) &
			      (dev->limits.num_mpts - 1));
	if (err)
		mthca_warn(dev, "HW2SW_MPT failed (%d)\n", err);

	mthca_free_region(dev, mr->ibmr.lkey);
	mthca_free_mtt(dev, mr->mtt);
}