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
struct mthca_profile {int num_uar; int /*<<< orphan*/  num_srq; scalar_t__ num_udav; } ;
struct mthca_init_hca_param {int dummy; } ;
struct mthca_dev_lim {int uar_size; int /*<<< orphan*/  max_srqs; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_icm; } ;
struct TYPE_4__ {TYPE_1__ arbel; } ;
struct mthca_dev {int mthca_flags; TYPE_2__ fw; } ;
typedef  int s64 ;

/* Variables and functions */
 int EAGAIN ; 
 int MTHCA_FLAG_NO_LAM ; 
 int MTHCA_FLAG_SRQ ; 
 int PAGE_SIZE ; 
 struct mthca_profile hca_profile ; 
 int /*<<< orphan*/  mthca_DISABLE_LAM (struct mthca_dev*) ; 
 int mthca_ENABLE_LAM (struct mthca_dev*) ; 
 int mthca_INIT_HCA (struct mthca_dev*,struct mthca_init_hca_param*) ; 
 int mthca_QUERY_FW (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_UNMAP_FA (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*) ; 
 int mthca_dev_lim (struct mthca_dev*,struct mthca_dev_lim*) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,int) ; 
 int /*<<< orphan*/  mthca_free_icm (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_icms (struct mthca_dev*) ; 
 int mthca_init_icm (struct mthca_dev*,struct mthca_dev_lim*,struct mthca_init_hca_param*,int) ; 
 int mthca_load_fw (struct mthca_dev*) ; 
 int mthca_make_profile (struct mthca_dev*,struct mthca_profile*,struct mthca_dev_lim*,struct mthca_init_hca_param*) ; 

__attribute__((used)) static int mthca_init_arbel(struct mthca_dev *mdev)
{
	struct mthca_dev_lim        dev_lim;
	struct mthca_profile        profile;
	struct mthca_init_hca_param init_hca;
	s64 icm_size;
	int err;

	err = mthca_QUERY_FW(mdev);
	if (err) {
		mthca_err(mdev, "QUERY_FW command failed %d, aborting.\n", err);
		return err;
	}

	err = mthca_ENABLE_LAM(mdev);
	if (err == -EAGAIN) {
		mthca_dbg(mdev, "No HCA-attached memory (running in MemFree mode)\n");
		mdev->mthca_flags |= MTHCA_FLAG_NO_LAM;
	} else if (err) {
		mthca_err(mdev, "ENABLE_LAM returned %d, aborting.\n", err);
		return err;
	}

	err = mthca_load_fw(mdev);
	if (err) {
		mthca_err(mdev, "Loading FW returned %d, aborting.\n", err);
		goto err_disable;
	}

	err = mthca_dev_lim(mdev, &dev_lim);
	if (err) {
		mthca_err(mdev, "QUERY_DEV_LIM returned %d, aborting.\n", err);
		goto err_stop_fw;
	}

	profile = hca_profile;
	profile.num_uar  = dev_lim.uar_size / PAGE_SIZE;
	profile.num_udav = 0;
	if (mdev->mthca_flags & MTHCA_FLAG_SRQ)
		profile.num_srq = dev_lim.max_srqs;

	icm_size = mthca_make_profile(mdev, &profile, &dev_lim, &init_hca);
	if (icm_size < 0) {
		err = icm_size;
		goto err_stop_fw;
	}

	err = mthca_init_icm(mdev, &dev_lim, &init_hca, icm_size);
	if (err)
		goto err_stop_fw;

	err = mthca_INIT_HCA(mdev, &init_hca);
	if (err) {
		mthca_err(mdev, "INIT_HCA command returned %d, aborting.\n", err);
		goto err_free_icm;
	}

	return 0;

err_free_icm:
	mthca_free_icms(mdev);

err_stop_fw:
	mthca_UNMAP_FA(mdev);
	mthca_free_icm(mdev, mdev->fw.arbel.fw_icm, 0);

err_disable:
	if (!(mdev->mthca_flags & MTHCA_FLAG_NO_LAM))
		mthca_DISABLE_LAM(mdev);

	return err;
}