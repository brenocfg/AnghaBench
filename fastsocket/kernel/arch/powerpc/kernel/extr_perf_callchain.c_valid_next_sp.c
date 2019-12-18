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
 unsigned long STACK_FRAME_OVERHEAD ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  validate_sp (unsigned long,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int valid_next_sp(unsigned long sp, unsigned long prev_sp)
{
	if (sp & 0xf)
		return 0;		/* must be 16-byte aligned */
	if (!validate_sp(sp, current, STACK_FRAME_OVERHEAD))
		return 0;
	if (sp >= prev_sp + STACK_FRAME_OVERHEAD)
		return 1;
	/*
	 * sp could decrease when we jump off an interrupt stack
	 * back to the regular process stack.
	 */
	if ((sp & ~(THREAD_SIZE - 1)) != (prev_sp & ~(THREAD_SIZE - 1)))
		return 1;
	return 0;
}