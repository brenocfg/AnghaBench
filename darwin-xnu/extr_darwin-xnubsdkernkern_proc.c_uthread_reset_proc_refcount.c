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
typedef  TYPE_1__* uthread_t ;
struct TYPE_2__ {scalar_t__ uu_proc_refcount; } ;

/* Variables and functions */

void
uthread_reset_proc_refcount(void *uthread) {
	uthread_t uth;

	uth = (uthread_t) uthread;
	uth->uu_proc_refcount = 0;

#if PROC_REF_DEBUG
	if (proc_ref_tracking_disabled) {
		return;
	}

	uth->uu_pindex = 0;
#endif
}