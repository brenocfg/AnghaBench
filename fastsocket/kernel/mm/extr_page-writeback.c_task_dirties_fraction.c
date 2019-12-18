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
struct task_struct {int /*<<< orphan*/  dirties; } ;

/* Variables and functions */
 int /*<<< orphan*/  prop_fraction_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*,long*) ; 
 int /*<<< orphan*/  vm_dirties ; 

__attribute__((used)) static inline void task_dirties_fraction(struct task_struct *tsk,
		long *numerator, long *denominator)
{
	prop_fraction_single(&vm_dirties, &tsk->dirties,
				numerator, denominator);
}