#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vt_notifier_param {struct vc_data* vc; } ;
struct vc_data {struct vc_data* vc_screenbuf; TYPE_1__* vc_sw; int /*<<< orphan*/  vt_pid; } ;
struct TYPE_4__ {struct vc_data* d; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* con_deinit ) (struct vc_data*) ;} ;

/* Variables and functions */
 unsigned int MIN_NR_CONSOLES ; 
 int /*<<< orphan*/  VT_DEALLOCATE ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vt_notifier_param*) ; 
 int /*<<< orphan*/  kfree (struct vc_data*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*) ; 
 TYPE_2__* vc_cons ; 
 scalar_t__ vc_cons_allocated (unsigned int) ; 
 int /*<<< orphan*/  vcs_remove_sysfs (unsigned int) ; 
 int /*<<< orphan*/  vt_notifier_list ; 

void vc_deallocate(unsigned int currcons)
{
	WARN_CONSOLE_UNLOCKED();

	if (vc_cons_allocated(currcons)) {
		struct vc_data *vc = vc_cons[currcons].d;
		struct vt_notifier_param param = { .vc = vc };

		atomic_notifier_call_chain(&vt_notifier_list, VT_DEALLOCATE, &param);
		vcs_remove_sysfs(currcons);
		vc->vc_sw->con_deinit(vc);
		put_pid(vc->vt_pid);
		module_put(vc->vc_sw->owner);
		kfree(vc->vc_screenbuf);
		if (currcons >= MIN_NR_CONSOLES)
			kfree(vc);
		vc_cons[currcons].d = NULL;
	}
}