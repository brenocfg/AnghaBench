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
struct ocfs2_super {struct ocfs2_dentry_lock* dentry_lock_list; int /*<<< orphan*/  dentry_lock_work; } ;
struct ocfs2_dentry_lock {struct ocfs2_dentry_lock* dl_next; int /*<<< orphan*/  dl_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_OSB_DROP_DENTRY_LOCK_IMMED ; 
 int /*<<< orphan*/  dentry_list_lock ; 
 int /*<<< orphan*/  ocfs2_lock_res_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_simple_drop_lockres (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_test_osb_flag (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_drop_dentry_lock(struct ocfs2_super *osb,
				   struct ocfs2_dentry_lock *dl)
{
	ocfs2_simple_drop_lockres(osb, &dl->dl_lockres);
	ocfs2_lock_res_free(&dl->dl_lockres);

	/* We leave dropping of inode reference to ocfs2_wq as that can
	 * possibly lead to inode deletion which gets tricky */
	spin_lock(&dentry_list_lock);
	if (!osb->dentry_lock_list &&
	    !ocfs2_test_osb_flag(osb, OCFS2_OSB_DROP_DENTRY_LOCK_IMMED))
		queue_work(ocfs2_wq, &osb->dentry_lock_work);
	dl->dl_next = osb->dentry_lock_list;
	osb->dentry_lock_list = dl;
	spin_unlock(&dentry_list_lock);
}