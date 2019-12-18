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
 int get_nr_irqs_gsi () ; 

__attribute__((used)) static int get_nr_hw_irqs(void)
{
	int ret = 1;

#ifdef CONFIG_X86_IO_APIC
	ret = get_nr_irqs_gsi();
#endif

	return ret;
}