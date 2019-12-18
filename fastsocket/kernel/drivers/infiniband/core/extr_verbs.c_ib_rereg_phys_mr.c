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
struct ib_phys_buf {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ib_mr {TYPE_1__* device; struct ib_pd* pd; int /*<<< orphan*/  usecnt; } ;
struct TYPE_2__ {int (* rereg_phys_mr ) (struct ib_mr*,int,struct ib_pd*,struct ib_phys_buf*,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOSYS ; 
 int IB_MR_REREG_PD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_mr*,int,struct ib_pd*,struct ib_phys_buf*,int,int,int /*<<< orphan*/ *) ; 

int ib_rereg_phys_mr(struct ib_mr *mr,
		     int mr_rereg_mask,
		     struct ib_pd *pd,
		     struct ib_phys_buf *phys_buf_array,
		     int num_phys_buf,
		     int mr_access_flags,
		     u64 *iova_start)
{
	struct ib_pd *old_pd;
	int ret;

	if (!mr->device->rereg_phys_mr)
		return -ENOSYS;

	if (atomic_read(&mr->usecnt))
		return -EBUSY;

	old_pd = mr->pd;

	ret = mr->device->rereg_phys_mr(mr, mr_rereg_mask, pd,
					phys_buf_array, num_phys_buf,
					mr_access_flags, iova_start);

	if (!ret && (mr_rereg_mask & IB_MR_REREG_PD)) {
		atomic_dec(&old_pd->usecnt);
		atomic_inc(&pd->usecnt);
	}

	return ret;
}