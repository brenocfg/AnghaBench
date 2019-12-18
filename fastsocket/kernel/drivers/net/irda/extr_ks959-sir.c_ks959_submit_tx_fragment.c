#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ks959_cb {unsigned int tx_buf_clear_used; unsigned int tx_buf_clear_sent; TYPE_2__* tx_urb; int /*<<< orphan*/  tx_buf_xored; TYPE_1__* tx_setuprequest; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  tx_buf_clear; } ;
struct TYPE_5__ {scalar_t__ status; } ;
struct TYPE_4__ {void* wLength; void* wValue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int KINGSUN_SND_PACKET_SIZE ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  ks959_send_irq ; 
 unsigned int obfuscate_tx_buffer (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct ks959_cb*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks959_submit_tx_fragment(struct ks959_cb *kingsun)
{
	unsigned int padlen;
	unsigned int wraplen;
	int ret;

	/* Check whether current plaintext can produce a padded buffer that fits
	   within the range handled by the dongle */
	wraplen = (KINGSUN_SND_PACKET_SIZE & ~0x7) - 0x10;
	if (wraplen > kingsun->tx_buf_clear_used)
		wraplen = kingsun->tx_buf_clear_used;

	/* Perform dongle obfuscation. Also remove the portion of the frame that
	   was just obfuscated and will now be sent to the dongle. */
	padlen = obfuscate_tx_buffer(kingsun->tx_buf_clear, wraplen,
				     kingsun->tx_buf_xored,
				     KINGSUN_SND_PACKET_SIZE);

	/* Calculate how much data can be transmitted in this urb */
	kingsun->tx_setuprequest->wValue = cpu_to_le16(wraplen);
	kingsun->tx_setuprequest->wLength = cpu_to_le16(padlen);
	/* Rest of the fields were filled in ks959_probe */
	usb_fill_control_urb(kingsun->tx_urb, kingsun->usbdev,
			     usb_sndctrlpipe(kingsun->usbdev, 0),
			     (unsigned char *)kingsun->tx_setuprequest,
			     kingsun->tx_buf_xored, padlen,
			     ks959_send_irq, kingsun);
	kingsun->tx_urb->status = 0;
	ret = usb_submit_urb(kingsun->tx_urb, GFP_ATOMIC);

	/* Remember how much data was sent, in order to update at callback */
	kingsun->tx_buf_clear_sent = (ret == 0) ? wraplen : 0;
	return ret;
}