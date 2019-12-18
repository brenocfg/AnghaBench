#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {TYPE_3__* dev; TYPE_1__* ep; } ;
struct mon_reader_bin {int /*<<< orphan*/  b_wait; int /*<<< orphan*/  b_lock; } ;
struct mon_bin_hdr {char type; unsigned long id; int status; char flag_setup; char flag_data; int /*<<< orphan*/  busnum; int /*<<< orphan*/  devnum; int /*<<< orphan*/  epnum; int /*<<< orphan*/  xfer_type; } ;
struct TYPE_6__ {TYPE_2__* bus; int /*<<< orphan*/  devnum; } ;
struct TYPE_5__ {int /*<<< orphan*/  busnum; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 struct mon_bin_hdr* MON_OFF2HDR (struct mon_reader_bin*,unsigned int) ; 
 int /*<<< orphan*/  PKT_SIZE ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  memset (struct mon_bin_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int mon_buff_area_alloc (struct mon_reader_bin*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_endpoint_num (int /*<<< orphan*/ *) ; 
 size_t usb_endpoint_type (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xfer_to_pipe ; 

__attribute__((used)) static void mon_bin_error(void *data, struct urb *urb, int error)
{
	struct mon_reader_bin *rp = data;
	unsigned long flags;
	unsigned int offset;
	struct mon_bin_hdr *ep;

	spin_lock_irqsave(&rp->b_lock, flags);

	offset = mon_buff_area_alloc(rp, PKT_SIZE);
	if (offset == ~0) {
		/* Not incrementing cnt_lost. Just because. */
		spin_unlock_irqrestore(&rp->b_lock, flags);
		return;
	}

	ep = MON_OFF2HDR(rp, offset);

	memset(ep, 0, PKT_SIZE);
	ep->type = 'E';
	ep->xfer_type = xfer_to_pipe[usb_endpoint_type(&urb->ep->desc)];
	ep->epnum = usb_urb_dir_in(urb) ? USB_DIR_IN : 0;
	ep->epnum |= usb_endpoint_num(&urb->ep->desc);
	ep->devnum = urb->dev->devnum;
	ep->busnum = urb->dev->bus->busnum;
	ep->id = (unsigned long) urb;
	ep->status = error;

	ep->flag_setup = '-';
	ep->flag_data = 'E';

	spin_unlock_irqrestore(&rp->b_lock, flags);

	wake_up(&rp->b_wait);
}