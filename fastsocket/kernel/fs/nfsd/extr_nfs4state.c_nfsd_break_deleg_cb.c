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
struct nfs4_delegation {TYPE_1__* dl_file; int /*<<< orphan*/  dl_time; int /*<<< orphan*/  dl_recall_lru; int /*<<< orphan*/  dl_count; } ;
struct file_lock {scalar_t__ fl_break_time; scalar_t__ fl_owner; } ;
struct TYPE_2__ {int fi_had_conflict; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_recall_lru ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_delegation*,struct file_lock*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_cb_recall (struct nfs4_delegation*) ; 
 int /*<<< orphan*/  recall_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void nfsd_break_deleg_cb(struct file_lock *fl)
{
	struct nfs4_delegation *dp = (struct nfs4_delegation *)fl->fl_owner;

	dprintk("NFSD nfsd_break_deleg_cb: dp %p fl %p\n",dp,fl);
	if (!dp)
		return;

	/* We're assuming the state code never drops its reference
	 * without first removing the lease.  Since we're in this lease
	 * callback (and since the lease code is serialized by the kernel
	 * lock) we know the server hasn't removed the lease yet, we know
	 * it's safe to take a reference: */
	atomic_inc(&dp->dl_count);

	spin_lock(&recall_lock);
	list_add_tail(&dp->dl_recall_lru, &del_recall_lru);
	spin_unlock(&recall_lock);

	/* only place dl_time is set. protected by lock_kernel*/
	dp->dl_time = get_seconds();

	/*
	 * We don't want the locks code to timeout the lease for us;
	 * we'll remove it ourself if the delegation isn't returned
	 * in time.
	 */
	fl->fl_break_time = 0;

	dp->dl_file->fi_had_conflict = true;
	nfsd4_cb_recall(dp);
}