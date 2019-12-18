#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {scalar_t__ status; scalar_t__ actual_length; int* transfer_buffer; struct ks959_cb* context; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct ks959_cb {int receiving; int rx_variable_xormask; TYPE_3__ rx_unwrap_buff; int /*<<< orphan*/  rx_time; TYPE_1__* netdev; } ;
typedef  int __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ OUTSIDE_FRAME ; 
 int /*<<< orphan*/  async_unwrap_char (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*,scalar_t__) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks959_rcv_irq(struct urb *urb)
{
	struct ks959_cb *kingsun = urb->context;
	int ret;

	/* in process of stopping, just drop data */
	if (!netif_running(kingsun->netdev)) {
		kingsun->receiving = 0;
		return;
	}

	/* unlink, shutdown, unplug, other nasties */
	if (urb->status != 0) {
		err("kingsun_rcv_irq: urb asynchronously failed - %d",
		    urb->status);
		kingsun->receiving = 0;
		return;
	}

	if (urb->actual_length > 0) {
		__u8 *bytes = urb->transfer_buffer;
		unsigned int i;

		for (i = 0; i < urb->actual_length; i++) {
			/* De-obfuscation implemented here: variable portion of
			   xormask is incremented, and then used with the encoded
			   byte for the XOR. The result of the operation is used
			   to unwrap the SIR frame. */
			kingsun->rx_variable_xormask++;
			bytes[i] =
			    bytes[i] ^ kingsun->rx_variable_xormask ^ 0x55u;

			/* rx_variable_xormask doubles as an index counter so we
			   can skip the byte at 0xff (wrapped around to 0).
			 */
			if (kingsun->rx_variable_xormask != 0) {
				async_unwrap_char(kingsun->netdev,
						  &kingsun->netdev->stats,
						  &kingsun->rx_unwrap_buff,
						  bytes[i]);
			}
		}
		do_gettimeofday(&kingsun->rx_time);
		kingsun->receiving =
		    (kingsun->rx_unwrap_buff.state != OUTSIDE_FRAME) ? 1 : 0;
	}

	/* This urb has already been filled in kingsun_net_open. Setup
	   packet must be re-filled, but it is assumed that urb keeps the
	   pointer to the initial setup packet, as well as the payload buffer.
	   Setup packet is already pre-filled at ks959_probe.
	 */
	urb->status = 0;
	ret = usb_submit_urb(urb, GFP_ATOMIC);
}