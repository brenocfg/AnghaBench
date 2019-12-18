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
 int /*<<< orphan*/  kernel_debug_string_early (char const*) ; 

__attribute__((used)) static inline void
vm_mem_bootstrap_log(const char *message)
{
//	kprintf("vm_mem_bootstrap: %s\n", message);
	kernel_debug_string_early(message);
}