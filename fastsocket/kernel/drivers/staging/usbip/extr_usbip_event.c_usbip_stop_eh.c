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
struct usbip_task {int /*<<< orphan*/  thread_done; } ;
struct usbip_device {struct usbip_task eh; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbip_dbg_eh (char*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void usbip_stop_eh(struct usbip_device *ud)
{
	struct usbip_task *eh = &ud->eh;

	wait_for_completion(&eh->thread_done);
	usbip_dbg_eh("usbip_eh has finished\n");
}