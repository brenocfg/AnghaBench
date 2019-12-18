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
struct ctl_table {scalar_t__ proc_handler; scalar_t__ strategy; scalar_t__ procname; scalar_t__ ctl_name; } ;

/* Variables and functions */
 scalar_t__ proc_dointvec ; 
 scalar_t__ sysctl_data ; 

__attribute__((used)) static void sysctl_repair_table(struct ctl_table *table)
{
	/* Don't complain about the classic default
	 * sysctl strategy routine.  Maybe later we
	 * can get the tables fixed and complain about
	 * this.
	 */
	if (table->ctl_name && table->procname &&
		(table->proc_handler == proc_dointvec) &&
		(!table->strategy)) {
		table->strategy = sysctl_data;
	}
}