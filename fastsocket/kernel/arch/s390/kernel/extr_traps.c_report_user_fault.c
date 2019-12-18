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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,long) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  sysctl_userprocess_debug ; 

__attribute__((used)) static void inline
report_user_fault(long interruption_code, struct pt_regs *regs)
{
#if defined(CONFIG_SYSCTL)
	if (!sysctl_userprocess_debug)
		return;
#endif
#if defined(CONFIG_SYSCTL) || defined(CONFIG_PROCESS_DEBUG)
	printk("User process fault: interruption code 0x%lX\n",
	       interruption_code);
	show_regs(regs);
#endif
}