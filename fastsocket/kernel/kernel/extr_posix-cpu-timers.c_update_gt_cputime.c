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
struct task_cputime {scalar_t__ sum_exec_runtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;

/* Variables and functions */
 scalar_t__ cputime_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_gt_cputime(struct task_cputime *a, struct task_cputime *b)
{
	if (cputime_gt(b->utime, a->utime))
		a->utime = b->utime;

	if (cputime_gt(b->stime, a->stime))
		a->stime = b->stime;

	if (b->sum_exec_runtime > a->sum_exec_runtime)
		a->sum_exec_runtime = b->sum_exec_runtime;
}