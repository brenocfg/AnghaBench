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

void vm_pageout_io_throttle(void) {
	struct uthread *uthread = get_bsdthread_info(current_thread());
 
               /*
                * thread is marked as a low priority I/O type
                * and the I/O we issued while in this cleaning operation
                * collided with normal I/O operations... we'll
                * delay in order to mitigate the impact of this
                * task on the normal operation of the system
                */

	if (uthread->uu_lowpri_window) {
		throttle_lowpri_io(1);
	}

}