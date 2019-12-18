#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_2__ {unsigned long id; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int LAST_CONTEXT ; 
 int /*<<< orphan*/  context_map ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,int,unsigned long) ; 
 unsigned long next_mmu_context ; 
 scalar_t__ test_and_set_bit (unsigned long,int /*<<< orphan*/ ) ; 

int init_new_context(struct task_struct *t, struct mm_struct *mm)
{
	unsigned long ctx = next_mmu_context;

	while (test_and_set_bit(ctx, context_map)) {
		ctx = find_next_zero_bit(context_map, LAST_CONTEXT+1, ctx);
		if (ctx > LAST_CONTEXT)
			ctx = 0;
	}
	next_mmu_context = (ctx + 1) & LAST_CONTEXT;
	mm->context.id = ctx;

	return 0;
}