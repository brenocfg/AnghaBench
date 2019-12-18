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
struct uthread {scalar_t__ uu_lowpri_window; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throttle_lowpri_io (int) ; 

void
vnode_pager_throttle()
{
	struct uthread *ut;

	ut = get_bsdthread_info(current_thread());

	if (ut->uu_lowpri_window)
		throttle_lowpri_io(1);
}