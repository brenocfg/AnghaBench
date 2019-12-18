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
struct TYPE_2__ {int num_ddr_avs; int /*<<< orphan*/  alloc; int /*<<< orphan*/  pool; int /*<<< orphan*/ * av_map; scalar_t__ ddr_av_base; } ;
struct mthca_dev {int mthca_flags; TYPE_1__ av_table; scalar_t__ ddr_start; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MTHCA_AV_SIZE ; 
 int MTHCA_FLAG_DDR_HIDDEN ; 
 int /*<<< orphan*/ * ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int mthca_alloc_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  pci_pool_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pool_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int) ; 

int mthca_init_av_table(struct mthca_dev *dev)
{
	int err;

	if (mthca_is_memfree(dev))
		return 0;

	err = mthca_alloc_init(&dev->av_table.alloc,
			       dev->av_table.num_ddr_avs,
			       dev->av_table.num_ddr_avs - 1,
			       0);
	if (err)
		return err;

	dev->av_table.pool = pci_pool_create("mthca_av", dev->pdev,
					     MTHCA_AV_SIZE,
					     MTHCA_AV_SIZE, 0);
	if (!dev->av_table.pool)
		goto out_free_alloc;

	if (!(dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN)) {
		dev->av_table.av_map = ioremap(pci_resource_start(dev->pdev, 4) +
					       dev->av_table.ddr_av_base -
					       dev->ddr_start,
					       dev->av_table.num_ddr_avs *
					       MTHCA_AV_SIZE);
		if (!dev->av_table.av_map)
			goto out_free_pool;
	} else
		dev->av_table.av_map = NULL;

	return 0;

 out_free_pool:
	pci_pool_destroy(dev->av_table.pool);

 out_free_alloc:
	mthca_alloc_cleanup(&dev->av_table.alloc);
	return -ENOMEM;
}