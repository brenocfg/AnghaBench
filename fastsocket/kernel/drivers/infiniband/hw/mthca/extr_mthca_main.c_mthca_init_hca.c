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
struct TYPE_2__ {int /*<<< orphan*/  inta_pin; } ;
struct mthca_dev {int /*<<< orphan*/  board_id; int /*<<< orphan*/  rev_id; TYPE_1__ eq_table; } ;
struct mthca_adapter {int /*<<< orphan*/  board_id; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  inta_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mthca_QUERY_ADAPTER (struct mthca_dev*,struct mthca_adapter*) ; 
 int /*<<< orphan*/  mthca_close_hca (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,int) ; 
 int mthca_init_arbel (struct mthca_dev*) ; 
 int mthca_init_tavor (struct mthca_dev*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

__attribute__((used)) static int mthca_init_hca(struct mthca_dev *mdev)
{
	int err;
	struct mthca_adapter adapter;

	if (mthca_is_memfree(mdev))
		err = mthca_init_arbel(mdev);
	else
		err = mthca_init_tavor(mdev);

	if (err)
		return err;

	err = mthca_QUERY_ADAPTER(mdev, &adapter);
	if (err) {
		mthca_err(mdev, "QUERY_ADAPTER command returned %d, aborting.\n", err);
		goto err_close;
	}

	mdev->eq_table.inta_pin = adapter.inta_pin;
	if (!mthca_is_memfree(mdev))
		mdev->rev_id = adapter.revision_id;
	memcpy(mdev->board_id, adapter.board_id, sizeof mdev->board_id);

	return 0;

err_close:
	mthca_close_hca(mdev);
	return err;
}