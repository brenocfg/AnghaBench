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
typedef  long u64 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (long,long) ; 
 int /*<<< orphan*/  task_dirties_fraction (struct task_struct*,long*,long*) ; 

__attribute__((used)) static void task_dirty_limit(struct task_struct *tsk, unsigned long *pdirty)
{
	long numerator, denominator;
	unsigned long dirty = *pdirty;
	u64 inv = dirty >> 3;

	task_dirties_fraction(tsk, &numerator, &denominator);
	inv *= numerator;
	do_div(inv, denominator);

	dirty -= inv;
	if (dirty < *pdirty/2)
		dirty = *pdirty/2;

	*pdirty = dirty;
}