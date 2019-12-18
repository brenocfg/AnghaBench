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
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_ge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_zero ; 

__attribute__((used)) static inline int task_cputime_expired(const struct task_cputime *sample,
					const struct task_cputime *expires)
{
	if (!cputime_eq(expires->utime, cputime_zero) &&
	    cputime_ge(sample->utime, expires->utime))
		return 1;
	if (!cputime_eq(expires->stime, cputime_zero) &&
	    cputime_ge(cputime_add(sample->utime, sample->stime),
		       expires->stime))
		return 1;
	if (expires->sum_exec_runtime != 0 &&
	    sample->sum_exec_runtime >= expires->sum_exec_runtime)
		return 1;
	return 0;
}