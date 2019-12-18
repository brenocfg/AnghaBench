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
struct TYPE_4__ {int /*<<< orphan*/  fw_icm; int /*<<< orphan*/  fw_pages; } ;
struct TYPE_3__ {TYPE_2__ arbel; } ;
struct mthca_dev {TYPE_1__ fw; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_HIGHUSER ; 
 int __GFP_NOWARN ; 
 int mthca_MAP_FA (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_RUN_FW (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_UNMAP_FA (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_alloc_icm (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,...) ; 
 int /*<<< orphan*/  mthca_free_icm (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_load_fw(struct mthca_dev *mdev)
{
	int err;

	/* FIXME: use HCA-attached memory for FW if present */

	mdev->fw.arbel.fw_icm =
		mthca_alloc_icm(mdev, mdev->fw.arbel.fw_pages,
				GFP_HIGHUSER | __GFP_NOWARN, 0);
	if (!mdev->fw.arbel.fw_icm) {
		mthca_err(mdev, "Couldn't allocate FW area, aborting.\n");
		return -ENOMEM;
	}

	err = mthca_MAP_FA(mdev, mdev->fw.arbel.fw_icm);
	if (err) {
		mthca_err(mdev, "MAP_FA command returned %d, aborting.\n", err);
		goto err_free;
	}
	err = mthca_RUN_FW(mdev);
	if (err) {
		mthca_err(mdev, "RUN_FW command returned %d, aborting.\n", err);
		goto err_unmap_fa;
	}

	return 0;

err_unmap_fa:
	mthca_UNMAP_FA(mdev);

err_free:
	mthca_free_icm(mdev, mdev->fw.arbel.fw_icm, 0);
	return err;
}