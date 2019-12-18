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
 int /*<<< orphan*/  paniclog_append_noflush (char*,void*) ; 
 scalar_t__ vm_kernel_slide ; 
 scalar_t__ vm_kernel_stext ; 

void
panic_display_kernel_aslr(void) {
	if (vm_kernel_slide) {
		paniclog_append_noflush("Kernel slide:     0x%016lx\n", (unsigned long) vm_kernel_slide);
		paniclog_append_noflush("Kernel text base: %p\n", (void *) vm_kernel_stext);
	}
}