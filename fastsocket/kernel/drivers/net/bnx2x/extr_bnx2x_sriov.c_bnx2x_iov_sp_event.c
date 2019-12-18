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
struct bnx2x_virtf {int /*<<< orphan*/  op_in_progress; } ;
struct bnx2x {int /*<<< orphan*/  sp_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SRIOV (struct bnx2x*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bnx2x_iov_is_vf_cid (struct bnx2x*,int) ; 
 struct bnx2x_virtf* bnx2x_vf_by_cid (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bnx2x_iov_sp_event(struct bnx2x *bp, int vf_cid, bool queue_work)
{
	struct bnx2x_virtf *vf;

	/* check if the cid is the VF range */
	if (!IS_SRIOV(bp) || !bnx2x_iov_is_vf_cid(bp, vf_cid))
		return;

	vf = bnx2x_vf_by_cid(bp, vf_cid);
	if (vf) {
		/* set in_progress flag */
		atomic_set(&vf->op_in_progress, 1);
		if (queue_work)
			queue_delayed_work(bnx2x_wq, &bp->sp_task, 0);
	}
}