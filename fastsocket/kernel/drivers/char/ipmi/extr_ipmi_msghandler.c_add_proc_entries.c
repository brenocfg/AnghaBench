#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipmi_smi_t ;
struct TYPE_5__ {int /*<<< orphan*/  proc_dir; int /*<<< orphan*/  proc_dir_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ipmb_file_read_proc ; 
 int ipmi_smi_add_proc_entry (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_ipmi_root ; 
 int /*<<< orphan*/  proc_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stat_file_read_proc ; 
 int /*<<< orphan*/  version_file_read_proc ; 

__attribute__((used)) static int add_proc_entries(ipmi_smi_t smi, int num)
{
	int rv = 0;

#ifdef CONFIG_PROC_FS
	sprintf(smi->proc_dir_name, "%d", num);
	smi->proc_dir = proc_mkdir(smi->proc_dir_name, proc_ipmi_root);
	if (!smi->proc_dir)
		rv = -ENOMEM;

	if (rv == 0)
		rv = ipmi_smi_add_proc_entry(smi, "stats",
					     stat_file_read_proc,
					     smi);

	if (rv == 0)
		rv = ipmi_smi_add_proc_entry(smi, "ipmb",
					     ipmb_file_read_proc,
					     smi);

	if (rv == 0)
		rv = ipmi_smi_add_proc_entry(smi, "version",
					     version_file_read_proc,
					     smi);
#endif /* CONFIG_PROC_FS */

	return rv;
}