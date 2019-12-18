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
struct unw_frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  print_symbol (char*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  unw_get_bsp (struct unw_frame_info*,unsigned long*) ; 
 int /*<<< orphan*/  unw_get_ip (struct unw_frame_info*,unsigned long*) ; 
 int /*<<< orphan*/  unw_get_sp (struct unw_frame_info*,unsigned long*) ; 
 scalar_t__ unw_unwind (struct unw_frame_info*) ; 

void
ia64_do_show_stack (struct unw_frame_info *info, void *arg)
{
	unsigned long ip, sp, bsp;
	char buf[128];			/* don't make it so big that it overflows the stack! */

	printk("\nCall Trace:\n");
	do {
		unw_get_ip(info, &ip);
		if (ip == 0)
			break;

		unw_get_sp(info, &sp);
		unw_get_bsp(info, &bsp);
		snprintf(buf, sizeof(buf),
			 " [<%016lx>] %%s\n"
			 "                                sp=%016lx bsp=%016lx\n",
			 ip, sp, bsp);
		print_symbol(buf, ip);
	} while (unw_unwind(info) >= 0);
}