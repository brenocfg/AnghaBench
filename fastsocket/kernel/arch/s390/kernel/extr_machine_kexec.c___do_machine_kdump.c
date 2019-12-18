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
struct kimage {scalar_t__ start; } ;

/* Variables and functions */
 int PSW_BASE_BITS ; 
 int PSW_DEFAULT_KEY ; 
 int /*<<< orphan*/  __load_psw_mask (int) ; 
 int /*<<< orphan*/  setup_regs () ; 

__attribute__((used)) static void __do_machine_kdump(void *image)
{
#ifdef CONFIG_CRASH_DUMP
	int (*start_kdump)(int) = (void *)((struct kimage *) image)->start;

	setup_regs();
	__load_psw_mask(PSW_BASE_BITS | PSW_DEFAULT_KEY);
	start_kdump(1);
#endif
}