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

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ds_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracers ; 

__attribute__((used)) static inline int get_tracer(struct task_struct *task)
{
	int error;

	spin_lock_irq(&ds_lock);

	if (task) {
		error = -EPERM;
		if (atomic_read(&tracers) < 0)
			goto out;
		atomic_inc(&tracers);
	} else {
		error = -EPERM;
		if (atomic_read(&tracers) > 0)
			goto out;
		atomic_dec(&tracers);
	}

	error = 0;
out:
	spin_unlock_irq(&ds_lock);
	return error;
}