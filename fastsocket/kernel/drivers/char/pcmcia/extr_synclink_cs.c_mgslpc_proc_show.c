#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* next_device; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  driver_version ; 
 int /*<<< orphan*/  line_info (struct seq_file*,TYPE_1__*) ; 
 TYPE_1__* mgslpc_device_list ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mgslpc_proc_show(struct seq_file *m, void *v)
{
	MGSLPC_INFO *info;

	seq_printf(m, "synclink driver:%s\n", driver_version);

	info = mgslpc_device_list;
	while( info ) {
		line_info(m, info);
		info = info->next_device;
	}
	return 0;
}