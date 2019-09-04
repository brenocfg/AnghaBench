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
 scalar_t__ vm_hib_base ; 

void
panic_display_hibb(void) {
#if defined(__i386__) || defined (__x86_64__)
	paniclog_append_noflush("__HIB  text base: %p\n", (void *) vm_hib_base);
#endif
}