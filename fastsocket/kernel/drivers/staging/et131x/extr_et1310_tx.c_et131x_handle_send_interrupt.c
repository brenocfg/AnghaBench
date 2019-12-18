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
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  et131x_check_send_wait_list (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_update_tcb_list (struct et131x_adapter*) ; 

void et131x_handle_send_interrupt(struct et131x_adapter *etdev)
{
	/* Mark as completed any packets which have been sent by the device. */
	et131x_update_tcb_list(etdev);

	/* If we queued any transmits because we didn't have any TCBs earlier,
	 * dequeue and send those packets now, as long as we have free TCBs.
	 */
	et131x_check_send_wait_list(etdev);
}