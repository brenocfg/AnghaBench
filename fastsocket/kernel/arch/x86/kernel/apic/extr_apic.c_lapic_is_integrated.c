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
 int APIC_INTEGRATED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_get_version () ; 

__attribute__((used)) static inline int lapic_is_integrated(void)
{
#ifdef CONFIG_X86_64
	return 1;
#else
	return APIC_INTEGRATED(lapic_get_version());
#endif
}