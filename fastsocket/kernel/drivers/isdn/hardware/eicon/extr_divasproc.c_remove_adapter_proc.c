#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; scalar_t__ proc_adapter_dir; scalar_t__ proc_info; scalar_t__ proc_grp_opt; scalar_t__ proc_d_l1_down; } ;
typedef  TYPE_1__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRC (char*) ; 
 char* adapter_dir_name ; 
 char* d_l1_down_proc_name ; 
 char* grp_opt_proc_name ; 
 char* info_proc_name ; 
 struct proc_dir_entry* proc_net_eicon ; 
 int /*<<< orphan*/  remove_proc_entry (char*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 

void remove_adapter_proc(diva_os_xdi_adapter_t * a)
{
	char tmp[16];

	if (a->proc_adapter_dir) {
		if (a->proc_d_l1_down) {
			remove_proc_entry(d_l1_down_proc_name,
					  (struct proc_dir_entry *) a->proc_adapter_dir);
		}
		if (a->proc_grp_opt) {
			remove_proc_entry(grp_opt_proc_name,
					  (struct proc_dir_entry *) a->proc_adapter_dir);
		}
		if (a->proc_info) {
			remove_proc_entry(info_proc_name,
					  (struct proc_dir_entry *) a->proc_adapter_dir);
		}
		sprintf(tmp, "%s%d", adapter_dir_name, a->controller);
		remove_proc_entry(tmp, proc_net_eicon);
		DBG_TRC(("proc entry %s%d removed", adapter_dir_name,
			 a->controller));
	}
}