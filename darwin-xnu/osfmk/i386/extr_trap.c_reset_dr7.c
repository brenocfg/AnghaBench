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

__attribute__((used)) static inline void
reset_dr7(void)
{
	long dr7 = 0x400; /* magic dr7 reset value; 32 bit on i386, 64 bit on x86_64 */
	__asm__ volatile("mov %0,%%dr7" : : "r" (dr7));
}