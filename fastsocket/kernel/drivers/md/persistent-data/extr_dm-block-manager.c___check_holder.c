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
struct stack_trace {int skip; int /*<<< orphan*/  entries; int /*<<< orphan*/  max_entries; scalar_t__ nr_entries; } ;
struct block_lock {scalar_t__* holders; struct stack_trace* traces; } ;
typedef  int /*<<< orphan*/  stack_entries ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 unsigned int MAX_HOLDERS ; 
 int /*<<< orphan*/  MAX_STACK ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  print_stack_trace (struct stack_trace*,int) ; 
 int /*<<< orphan*/  save_stack_trace (struct stack_trace*) ; 

__attribute__((used)) static int __check_holder(struct block_lock *lock)
{
	unsigned i;
#ifdef CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
	static struct stack_trace t;
	static stack_entries entries;
#endif

	for (i = 0; i < MAX_HOLDERS; i++) {
		if (lock->holders[i] == current) {
			DMERR("recursive lock detected in metadata");
#ifdef CONFIG_DM_DEBUG_BLOCK_STACK_TRACING
			DMERR("previously held here:");
			print_stack_trace(lock->traces + i, 4);

			DMERR("subsequent acquisition attempted here:");
			t.nr_entries = 0;
			t.max_entries = MAX_STACK;
			t.entries = entries;
			t.skip = 3;
			save_stack_trace(&t);
			print_stack_trace(&t, 4);
#endif
			return -EINVAL;
		}
	}

	return 0;
}