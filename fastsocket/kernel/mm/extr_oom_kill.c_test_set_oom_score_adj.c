#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sighand_struct {int /*<<< orphan*/  siglock; } ;
struct TYPE_6__ {TYPE_2__* signal; TYPE_1__* mm; struct sighand_struct* sighand; } ;
struct TYPE_5__ {int oom_score_adj; } ;
struct TYPE_4__ {int /*<<< orphan*/  oom_disable_count; } ;

/* Variables and functions */
 int OOM_SCORE_ADJ_MIN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int test_set_oom_score_adj(int new_val)
{
	struct sighand_struct *sighand = current->sighand;
	int old_val;

	spin_lock_irq(&sighand->siglock);
	old_val = current->signal->oom_score_adj;
	if (new_val != old_val) {
		if (new_val == OOM_SCORE_ADJ_MIN)
			atomic_inc(&current->mm->oom_disable_count);
		else if (old_val == OOM_SCORE_ADJ_MIN)
			atomic_dec(&current->mm->oom_disable_count);
		current->signal->oom_score_adj = new_val;
	}
	spin_unlock_irq(&sighand->siglock);

	return old_val;
}