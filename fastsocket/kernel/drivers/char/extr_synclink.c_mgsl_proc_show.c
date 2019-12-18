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
struct seq_file {int dummy; } ;
struct mgsl_struct {struct mgsl_struct* next_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_version ; 
 int /*<<< orphan*/  line_info (struct seq_file*,struct mgsl_struct*) ; 
 struct mgsl_struct* mgsl_device_list ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mgsl_proc_show(struct seq_file *m, void *v)
{
	struct mgsl_struct *info;
	
	seq_printf(m, "synclink driver:%s\n", driver_version);
	
	info = mgsl_device_list;
	while( info ) {
		line_info(m, info);
		info = info->next_device;
	}
	return 0;
}