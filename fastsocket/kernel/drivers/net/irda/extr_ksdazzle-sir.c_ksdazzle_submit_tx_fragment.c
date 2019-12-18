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
struct ksdazzle_cb {unsigned int tx_buf_clear_used; unsigned char* tx_payload; unsigned int tx_buf_clear_sent; TYPE_1__* tx_urb; int /*<<< orphan*/  ep_out; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  tx_buf_clear; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ksdazzle_send_irq ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,struct ksdazzle_cb*,int) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ksdazzle_submit_tx_fragment(struct ksdazzle_cb *kingsun)
{
	unsigned int wraplen;
	int ret;

	/* We can send at most 7 bytes of payload at a time */
	wraplen = 7;
	if (wraplen > kingsun->tx_buf_clear_used)
		wraplen = kingsun->tx_buf_clear_used;

	/* Prepare payload prefix with used length */
	memset(kingsun->tx_payload, 0, 8);
	kingsun->tx_payload[0] = (unsigned char)0xf8 + wraplen;
	memcpy(kingsun->tx_payload + 1, kingsun->tx_buf_clear, wraplen);

	usb_fill_int_urb(kingsun->tx_urb, kingsun->usbdev,
			 usb_sndintpipe(kingsun->usbdev, kingsun->ep_out),
			 kingsun->tx_payload, 8, ksdazzle_send_irq, kingsun, 1);
	kingsun->tx_urb->status = 0;
	ret = usb_submit_urb(kingsun->tx_urb, GFP_ATOMIC);

	/* Remember how much data was sent, in order to update at callback */
	kingsun->tx_buf_clear_sent = (ret == 0) ? wraplen : 0;
	return ret;
}