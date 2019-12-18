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
 int /*<<< orphan*/  need_resched () ; 

__attribute__((used)) static void default_idle(void)
{
	if (!need_resched())
#if defined(MACH_ATARI_ONLY)
		/* block out HSYNC on the atari (falcon) */
		__asm__("stop #0x2200" : : : "cc");
#else
		__asm__("stop #0x2000" : : : "cc");
#endif
}