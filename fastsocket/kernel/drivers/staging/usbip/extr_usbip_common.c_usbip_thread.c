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
struct usbip_task {int /*<<< orphan*/  thread_done; int /*<<< orphan*/ * thread; int /*<<< orphan*/  (* loop_ops ) (struct usbip_task*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_and_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  daemonize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  stub1 (struct usbip_task*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int usbip_thread(void *param)
{
	struct usbip_task *ut = param;

	if (!ut)
		return -EINVAL;

	lock_kernel();
	daemonize(ut->name);
	allow_signal(SIGKILL);
	ut->thread = current;
	unlock_kernel();

	/* srv.rb must wait for rx_thread starting */
	complete(&ut->thread_done);

	/* start of while loop */
	ut->loop_ops(ut);

	/* end of loop */
	ut->thread = NULL;

	complete_and_exit(&ut->thread_done, 0);
}