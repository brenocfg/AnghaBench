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

/* Variables and functions */
 int /*<<< orphan*/  __show_stack (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  current ; 

void dump_stack(void)
{
	/*
	 * We need frame pointers for this little trick, which works as follows:
	 *
	 * +------------+ 0x00
	 * | Next SP	|	-> 0x0c
	 * +------------+ 0x04
	 * | Caller	|
	 * +------------+ 0x08
	 * | Local vars	|	-> our stack var
	 * +------------+ 0x0c
	 * | Next SP	|	-> 0x18, that is what we pass to show_stack()
	 * +------------+ 0x10
	 * | Caller	|
	 * +------------+ 0x14
	 * | Local vars	|
	 * +------------+ 0x18
	 * | ...	|
	 * +------------+
	 */

	unsigned long *stack;

	stack = (unsigned long *)&stack;
	stack++;
	__show_stack(current, stack);
}