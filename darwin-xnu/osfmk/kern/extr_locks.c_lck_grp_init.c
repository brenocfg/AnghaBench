#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_6__ {int lck_grp_refcnt; int /*<<< orphan*/  lck_grp_attr; int /*<<< orphan*/  lck_grp_name; } ;
typedef  TYPE_1__ lck_grp_t ;
struct TYPE_7__ {int /*<<< orphan*/  grp_attr_val; } ;
typedef  TYPE_2__ lck_grp_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NONE ; 
 TYPE_2__* LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_STAT ; 
 int /*<<< orphan*/  LCK_GRP_MAX_NAME ; 
 int LcksOpts ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int enaLkStat ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lck_grp_cnt ; 
 int /*<<< orphan*/  lck_grp_lock ; 
 int /*<<< orphan*/  lck_grp_queue ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
lck_grp_init(lck_grp_t * grp, const char * grp_name, lck_grp_attr_t * attr)
{
	/* make sure locking infrastructure has been initialized */
	assert(lck_grp_cnt > 0);

	bzero((void *)grp, sizeof(lck_grp_t));

	(void)strlcpy(grp->lck_grp_name, grp_name, LCK_GRP_MAX_NAME);

	if (attr != LCK_GRP_ATTR_NULL)
		grp->lck_grp_attr = attr->grp_attr_val;
	else if (LcksOpts & enaLkStat)
		grp->lck_grp_attr = LCK_GRP_ATTR_STAT;
	else
		grp->lck_grp_attr = LCK_ATTR_NONE;

	grp->lck_grp_refcnt = 1;

	lck_mtx_lock(&lck_grp_lock);
	enqueue_tail(&lck_grp_queue, (queue_entry_t)grp);
	lck_grp_cnt++;
	lck_mtx_unlock(&lck_grp_lock);
}