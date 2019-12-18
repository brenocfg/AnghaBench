#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {int actual_length; int* transfer_buffer; scalar_t__ status; struct mcs_cb* context; } ;
struct mcs_cb {int speed; int /*<<< orphan*/  rx_time; int /*<<< orphan*/  rx_buff; TYPE_1__* netdev; } ;
typedef  int __u8 ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  async_unwrap_char (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcs_unwrap_fir (struct mcs_cb*,int*,int) ; 
 int /*<<< orphan*/  mcs_unwrap_mir (struct mcs_cb*,int*,int) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcs_receive_irq(struct urb *urb)
{
	__u8 *bytes;
	struct mcs_cb *mcs = urb->context;
	int i;
	int ret;

	if (!netif_running(mcs->netdev))
		return;

	if (urb->status)
		return;

	if (urb->actual_length > 0) {
		bytes = urb->transfer_buffer;

		/* MCS returns frames without BOF and EOF
		 * I assume it returns whole frames.
		 */
		/* SIR speed */
		if(mcs->speed < 576000) {
			async_unwrap_char(mcs->netdev, &mcs->netdev->stats,
				  &mcs->rx_buff, 0xc0);

			for (i = 0; i < urb->actual_length; i++)
				async_unwrap_char(mcs->netdev, &mcs->netdev->stats,
					  &mcs->rx_buff, bytes[i]);

			async_unwrap_char(mcs->netdev, &mcs->netdev->stats,
				  &mcs->rx_buff, 0xc1);
		}
		/* MIR speed */
		else if(mcs->speed == 576000 || mcs->speed == 1152000) {
			mcs_unwrap_mir(mcs, urb->transfer_buffer,
				urb->actual_length);
		}
		/* FIR speed */
		else {
			mcs_unwrap_fir(mcs, urb->transfer_buffer,
				urb->actual_length);
		}
		do_gettimeofday(&mcs->rx_time);
	}

	ret = usb_submit_urb(urb, GFP_ATOMIC);
}