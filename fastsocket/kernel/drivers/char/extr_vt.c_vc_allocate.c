#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vt_notifier_param {struct vc_data* vc; } ;
struct vc_data {int /*<<< orphan*/  vc_cols; int /*<<< orphan*/  vc_rows; int /*<<< orphan*/  vc_screenbuf; int /*<<< orphan*/  vc_screenbuf_size; int /*<<< orphan*/ * vc_uni_pagedir_loc; } ;
struct TYPE_2__ {struct vc_data* d; int /*<<< orphan*/  SAK_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MAX_NR_CONSOLES ; 
 unsigned int MAX_NR_USER_CONSOLES ; 
 int /*<<< orphan*/  VT_ALLOCATE ; 
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vt_notifier_param*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_set_default_unimap (struct vc_data*) ; 
 int /*<<< orphan*/  kfree (struct vc_data*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_SAK ; 
 TYPE_1__* vc_cons ; 
 int /*<<< orphan*/  vc_init (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcs_make_sysfs (unsigned int) ; 
 int /*<<< orphan*/  visual_init (struct vc_data*,unsigned int,int) ; 
 int /*<<< orphan*/  vt_notifier_list ; 

int vc_allocate(unsigned int currcons)	/* return 0 on success */
{
	WARN_CONSOLE_UNLOCKED();

	if (currcons >= MAX_NR_CONSOLES)
		return -ENXIO;
	if (!vc_cons[currcons].d) {
	    struct vc_data *vc;
	    struct vt_notifier_param param;

	    /* prevent users from taking too much memory */
	    if (currcons >= MAX_NR_USER_CONSOLES && !capable(CAP_SYS_RESOURCE))
	      return -EPERM;

	    /* due to the granularity of kmalloc, we waste some memory here */
	    /* the alloc is done in two steps, to optimize the common situation
	       of a 25x80 console (structsize=216, screenbuf_size=4000) */
	    /* although the numbers above are not valid since long ago, the
	       point is still up-to-date and the comment still has its value
	       even if only as a historical artifact.  --mj, July 1998 */
	    param.vc = vc = kzalloc(sizeof(struct vc_data), GFP_KERNEL);
	    if (!vc)
		return -ENOMEM;
	    vc_cons[currcons].d = vc;
	    INIT_WORK(&vc_cons[currcons].SAK_work, vc_SAK);
	    visual_init(vc, currcons, 1);
	    if (!*vc->vc_uni_pagedir_loc)
		con_set_default_unimap(vc);
	    vc->vc_screenbuf = kmalloc(vc->vc_screenbuf_size, GFP_KERNEL);
	    if (!vc->vc_screenbuf) {
		kfree(vc);
		vc_cons[currcons].d = NULL;
		return -ENOMEM;
	    }
	    vc_init(vc, vc->vc_rows, vc->vc_cols, 1);
	    vcs_make_sysfs(currcons);
	    atomic_notifier_call_chain(&vt_notifier_list, VT_ALLOCATE, &param);
	}
	return 0;
}