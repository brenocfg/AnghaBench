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

__attribute__((used)) static inline void cmf_activate(void *area, unsigned int onoff)
{
	register void * __gpr2 asm("2");
	register long __gpr1 asm("1");

	__gpr2 = area;
	__gpr1 = onoff ? 2 : 0;
	/* activate channel measurement */
	asm("schm" : : "d" (__gpr2), "d" (__gpr1) );
}