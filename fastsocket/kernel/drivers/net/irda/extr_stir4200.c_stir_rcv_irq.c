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
struct urb {scalar_t__ status; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; struct stir_cb* context; } ;
struct stir_cb {int /*<<< orphan*/  thread; scalar_t__ receiving; TYPE_1__* netdev; int /*<<< orphan*/  rx_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unwrap_chars (struct stir_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stir_rcv_irq(struct urb *urb)
{
	struct stir_cb *stir = urb->context;
	int err;

	/* in process of stopping, just drop data */
	if (!netif_running(stir->netdev))
		return;

	/* unlink, shutdown, unplug, other nasties */
	if (urb->status != 0) 
		return;

	if (urb->actual_length > 0) {
		pr_debug("receive %d\n", urb->actual_length);
		unwrap_chars(stir, urb->transfer_buffer,
			     urb->actual_length);
		
		do_gettimeofday(&stir->rx_time);
	}

	/* kernel thread is stopping receiver don't resubmit */
	if (!stir->receiving)
		return;

	/* resubmit existing urb */
	err = usb_submit_urb(urb, GFP_ATOMIC);

	/* in case of error, the kernel thread will restart us */
	if (err) {
		dev_warn(&stir->netdev->dev, "usb receive submit error: %d\n",
			 err);
		stir->receiving = 0;
		wake_up_process(stir->thread);
	}
}