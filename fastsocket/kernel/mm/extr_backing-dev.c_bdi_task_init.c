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
struct task_struct {int flags; } ;
struct bdi_writeback {int /*<<< orphan*/  list; } ;
struct backing_dev_info {int /*<<< orphan*/  wb_lock; int /*<<< orphan*/  wb_list; } ;

/* Variables and functions */
 int PF_FLUSHER ; 
 int PF_SWAPWRITE ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  set_user_nice (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bdi_task_init(struct backing_dev_info *bdi,
			  struct bdi_writeback *wb)
{
	struct task_struct *tsk = current;

	spin_lock(&bdi->wb_lock);
	list_add_tail_rcu(&wb->list, &bdi->wb_list);
	spin_unlock(&bdi->wb_lock);

	tsk->flags |= PF_FLUSHER | PF_SWAPWRITE;
	set_freezable();

	/*
	 * Our parent may run at a different priority, just set us to normal
	 */
	set_user_nice(tsk, 0);
}