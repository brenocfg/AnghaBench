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
struct quotafile {int /*<<< orphan*/  qf_lock; scalar_t__ qf_qflags; int /*<<< orphan*/  qf_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLVP ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qf_lck_attr ; 
 int /*<<< orphan*/  qf_lck_grp ; 

void
dqfileinit(struct quotafile *qfp)
{
        qfp->qf_vp = NULLVP;
	qfp->qf_qflags = 0;

	lck_mtx_init(&qfp->qf_lock, qf_lck_grp, qf_lck_attr);
}