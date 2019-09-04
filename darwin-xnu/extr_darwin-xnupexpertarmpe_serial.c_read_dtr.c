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
 int /*<<< orphan*/  panic_unimplemented () ; 

__attribute__((used)) static unsigned int
read_dtr(void)
{
#ifdef __arm__
	unsigned int	c;
	__asm__ volatile(
		"mrc p14, 0, %0, c0, c5\n"
:		"=r"(c));
	return c;
#else
	/* ARM64_TODO */
	panic_unimplemented();
	return 0;
#endif
}