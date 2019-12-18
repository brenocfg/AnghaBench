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
struct task_struct {int dummy; } ;
struct kioctx {int /*<<< orphan*/  ctx_lock; int /*<<< orphan*/  wait; scalar_t__ reqs_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void wait_for_all_aios(struct kioctx *ctx)
{
	struct task_struct *tsk = current;
	DECLARE_WAITQUEUE(wait, tsk);

	spin_lock_irq(&ctx->ctx_lock);
	if (!ctx->reqs_active)
		goto out;

	add_wait_queue(&ctx->wait, &wait);
	set_task_state(tsk, TASK_UNINTERRUPTIBLE);
	while (ctx->reqs_active) {
		spin_unlock_irq(&ctx->ctx_lock);
		io_schedule();
		set_task_state(tsk, TASK_UNINTERRUPTIBLE);
		spin_lock_irq(&ctx->ctx_lock);
	}
	__set_task_state(tsk, TASK_RUNNING);
	remove_wait_queue(&ctx->wait, &wait);

out:
	spin_unlock_irq(&ctx->ctx_lock);
}