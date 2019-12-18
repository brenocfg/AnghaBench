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
struct utrace_report {int /*<<< orphan*/  action; scalar_t__ detaches; scalar_t__ spurious; } ;
struct utrace {int /*<<< orphan*/  lock; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UTRACE_RESUME ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ utrace_reset (struct task_struct*,struct utrace*) ; 

__attribute__((used)) static inline void finish_report_reset(struct task_struct *task,
				       struct utrace *utrace,
				       struct utrace_report *report)
{
	if (unlikely(report->spurious || report->detaches)) {
		spin_lock(&utrace->lock);
		if (utrace_reset(task, utrace))
			report->action = UTRACE_RESUME;
	}
}