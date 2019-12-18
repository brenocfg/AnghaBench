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
struct TYPE_4__ {int /*<<< orphan*/  thread_done; int /*<<< orphan*/ * thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  thread_done; int /*<<< orphan*/ * thread; } ;
struct usbip_device {TYPE_2__ tcp_tx; TYPE_1__ tcp_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbip_udbg (char*,struct usbip_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void usbip_stop_threads(struct usbip_device *ud)
{
	/* kill threads related to this sdev, if v.c. exists */
	if (ud->tcp_rx.thread != NULL) {
		send_sig(SIGKILL, ud->tcp_rx.thread, 1);
		wait_for_completion(&ud->tcp_rx.thread_done);
		usbip_udbg("rx_thread for ud %p has finished\n", ud);
	}

	if (ud->tcp_tx.thread != NULL) {
		send_sig(SIGKILL, ud->tcp_tx.thread, 1);
		wait_for_completion(&ud->tcp_tx.thread_done);
		usbip_udbg("tx_thread for ud %p has finished\n", ud);
	}
}