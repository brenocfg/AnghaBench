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
struct fd_vn_data {int /*<<< orphan*/  fv_lock; struct fd_vn_data* fv_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct fd_vn_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FD_DIRBUF ; 
 int /*<<< orphan*/  M_FD_VN_DATA ; 
 int /*<<< orphan*/  fd_vn_lck_grp ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fg_vn_data_free(void *fgvndata)
{
	struct fd_vn_data *fvdata = (struct fd_vn_data *)fgvndata;

	if (fvdata->fv_buf)
		FREE(fvdata->fv_buf, M_FD_DIRBUF);
	lck_mtx_destroy(&fvdata->fv_lock, fd_vn_lck_grp);
	FREE(fvdata, M_FD_VN_DATA);
}