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
 scalar_t__ cputime_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_zero ; 

__attribute__((used)) static inline int task_cputime_zero(const struct task_cputime *cputime)
{
	if (cputime_eq(cputime->utime, cputime_zero) &&
	    cputime_eq(cputime->stime, cputime_zero) &&
	    cputime->sum_exec_runtime == 0)
		return 1;
	return 0;
}