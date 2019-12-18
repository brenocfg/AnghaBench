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
struct proc_dir_entry {TYPE_1__* data; int /*<<< orphan*/  read_proc; int /*<<< orphan*/  write_proc; } ;
struct TYPE_3__ {void* proc_d_l1_down; void* proc_grp_opt; void* proc_info; void* proc_adapter_dir; int /*<<< orphan*/  controller; } ;
typedef  TYPE_1__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRC (char*) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 char* adapter_dir_name ; 
 struct proc_dir_entry* create_proc_entry (int /*<<< orphan*/ ,int,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  d_l1_down_proc_name ; 
 int /*<<< orphan*/  grp_opt_proc_name ; 
 int /*<<< orphan*/  info_proc_name ; 
 int /*<<< orphan*/  info_read ; 
 int /*<<< orphan*/  info_write ; 
 struct proc_dir_entry* proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_net_eicon ; 
 int /*<<< orphan*/  read_d_l1_down ; 
 int /*<<< orphan*/  read_grp_opt ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_d_l1_down ; 
 int /*<<< orphan*/  write_grp_opt ; 

int create_adapter_proc(diva_os_xdi_adapter_t * a)
{
	struct proc_dir_entry *de, *pe;
	char tmp[16];

	sprintf(tmp, "%s%d", adapter_dir_name, a->controller);
	if (!(de = proc_mkdir(tmp, proc_net_eicon)))
		return (0);
	a->proc_adapter_dir = (void *) de;

	if (!(pe =
	     create_proc_entry(info_proc_name, S_IFREG | S_IRUGO | S_IWUSR, de)))
		return (0);
	a->proc_info = (void *) pe;
	pe->write_proc = info_write;
	pe->read_proc = info_read;
	pe->data = a;

	if ((pe = create_proc_entry(grp_opt_proc_name,
			       S_IFREG | S_IRUGO | S_IWUSR, de))) {
		a->proc_grp_opt = (void *) pe;
		pe->write_proc = write_grp_opt;
		pe->read_proc = read_grp_opt;
		pe->data = a;
	}
	if ((pe = create_proc_entry(d_l1_down_proc_name,
			       S_IFREG | S_IRUGO | S_IWUSR, de))) {
		a->proc_d_l1_down = (void *) pe;
		pe->write_proc = write_d_l1_down;
		pe->read_proc = read_d_l1_down;
		pe->data = a;
	}

	DBG_TRC(("proc entry %s created", tmp));

	return (1);
}