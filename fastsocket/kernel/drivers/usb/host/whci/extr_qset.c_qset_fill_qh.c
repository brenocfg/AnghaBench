#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* cur_window; void* info3; void* info2; void* info1; } ;
struct whc_qset {int max_seq; int max_burst; TYPE_4__ qh; int /*<<< orphan*/  max_packet; TYPE_3__* ep; } ;
struct usb_wireless_ep_comp_descriptor {int bMaxSequence; int bMaxBurst; } ;
struct usb_device {int /*<<< orphan*/  portnum; } ;
struct urb {int /*<<< orphan*/  pipe; TYPE_2__* ep; struct usb_device* dev; } ;
struct TYPE_7__ {scalar_t__ extra; } ;
struct TYPE_5__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int QH_INFO1_DEV_INFO_IDX (int /*<<< orphan*/ ) ; 
 int QH_INFO1_DIR_IN ; 
 int QH_INFO1_DIR_OUT ; 
 int QH_INFO1_EP (int /*<<< orphan*/ ) ; 
 int QH_INFO1_MAX_PKT_LEN (int /*<<< orphan*/ ) ; 
 int QH_INFO2_BURST (int) ; 
 int QH_INFO2_DBP (int /*<<< orphan*/ ) ; 
 int QH_INFO2_MAX_COUNT (int) ; 
 int QH_INFO2_MAX_RETRY (int) ; 
 int QH_INFO2_MAX_SEQ (int /*<<< orphan*/ ) ; 
 int QH_INFO3_TX_PWR (int /*<<< orphan*/ ) ; 
 int QH_INFO3_TX_RATE_53_3 ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_pipe_to_qh_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 int usb_pipeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_port_no_to_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qset_fill_qh(struct whc_qset *qset, struct urb *urb)
{
	struct usb_device *usb_dev = urb->dev;
	struct usb_wireless_ep_comp_descriptor *epcd;
	bool is_out;

	is_out = usb_pipeout(urb->pipe);

	qset->max_packet = le16_to_cpu(urb->ep->desc.wMaxPacketSize);

	epcd = (struct usb_wireless_ep_comp_descriptor *)qset->ep->extra;
	if (epcd) {
		qset->max_seq = epcd->bMaxSequence;
		qset->max_burst = epcd->bMaxBurst;
	} else {
		qset->max_seq = 2;
		qset->max_burst = 1;
	}

	qset->qh.info1 = cpu_to_le32(
		QH_INFO1_EP(usb_pipeendpoint(urb->pipe))
		| (is_out ? QH_INFO1_DIR_OUT : QH_INFO1_DIR_IN)
		| usb_pipe_to_qh_type(urb->pipe)
		| QH_INFO1_DEV_INFO_IDX(wusb_port_no_to_idx(usb_dev->portnum))
		| QH_INFO1_MAX_PKT_LEN(qset->max_packet)
		);
	qset->qh.info2 = cpu_to_le32(
		QH_INFO2_BURST(qset->max_burst)
		| QH_INFO2_DBP(0)
		| QH_INFO2_MAX_COUNT(3)
		| QH_INFO2_MAX_RETRY(3)
		| QH_INFO2_MAX_SEQ(qset->max_seq - 1)
		);
	/* FIXME: where can we obtain these Tx parameters from?  Why
	 * doesn't the chip know what Tx power to use? It knows the Rx
	 * strength and can presumably guess the Tx power required
	 * from that? */
	qset->qh.info3 = cpu_to_le32(
		QH_INFO3_TX_RATE_53_3
		| QH_INFO3_TX_PWR(0) /* 0 == max power */
		);

	qset->qh.cur_window = cpu_to_le32((1 << qset->max_burst) - 1);
}