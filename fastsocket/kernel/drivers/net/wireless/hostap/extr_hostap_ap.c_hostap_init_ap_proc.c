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
struct ap_data {int /*<<< orphan*/ * proc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * proc; struct ap_data* ap; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ap_control_proc_fops ; 
 int /*<<< orphan*/  ap_debug_proc_fops ; 
 int /*<<< orphan*/  prism2_ap_proc_fops ; 
 int /*<<< orphan*/  proc_create_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ap_data*) ; 

void hostap_init_ap_proc(local_info_t *local)
{
	struct ap_data *ap = local->ap;

	ap->proc = local->proc;
	if (ap->proc == NULL)
		return;

#ifndef PRISM2_NO_PROCFS_DEBUG
	proc_create_data("ap_debug", 0, ap->proc, &ap_debug_proc_fops, ap);
#endif /* PRISM2_NO_PROCFS_DEBUG */

#ifndef PRISM2_NO_KERNEL_IEEE80211_MGMT
	proc_create_data("ap_control", 0, ap->proc, &ap_control_proc_fops, ap);
	proc_create_data("ap", 0, ap->proc, &prism2_ap_proc_fops, ap);
#endif /* PRISM2_NO_KERNEL_IEEE80211_MGMT */

}