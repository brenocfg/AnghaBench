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
 int /*<<< orphan*/  ia32_boot_gdt_init () ; 
 int /*<<< orphan*/  ia32_gate_page_init () ; 

void
ia32_mem_init(void)
{
	ia32_boot_gdt_init();
	ia32_gate_page_init();
}