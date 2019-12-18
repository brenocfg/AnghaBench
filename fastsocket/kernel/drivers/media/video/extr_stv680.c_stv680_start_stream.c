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
struct usb_stv {int streaming; int maxframesize; TYPE_3__* scratch; TYPE_2__* sbuf; struct urb** urb; scalar_t__ framecount; int /*<<< orphan*/  rawbufsize; int /*<<< orphan*/  bulk_in_endpointAddr; int /*<<< orphan*/  udev; scalar_t__ scratch_overflow; scalar_t__ scratch_use; scalar_t__ scratch_next; TYPE_1__* frame; scalar_t__ fbuf; } ;
struct urb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {scalar_t__ curpix; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_UNUSED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,...) ; 
 int STV680_NUMFRAMES ; 
 int STV680_NUMSBUF ; 
 int STV680_NUMSCRATCH ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv680_video_irq ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_stv*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv680_start_stream (struct usb_stv *stv680)
{
	struct urb *urb;
	int err = 0, i;

	stv680->streaming = 1;

	/* Do some memory allocation */
	for (i = 0; i < STV680_NUMFRAMES; i++) {
		stv680->frame[i].data = stv680->fbuf + i * stv680->maxframesize;
		stv680->frame[i].curpix = 0;
	}
	/* packet size = 4096  */
	for (i = 0; i < STV680_NUMSBUF; i++) {
		stv680->sbuf[i].data = kmalloc (stv680->rawbufsize, GFP_KERNEL);
		if (stv680->sbuf[i].data == NULL) {
			PDEBUG (0, "STV(e): Could not kmalloc raw data buffer %i", i);
			goto nomem_err;
		}
	}

	stv680->scratch_next = 0;
	stv680->scratch_use = 0;
	stv680->scratch_overflow = 0;
	for (i = 0; i < STV680_NUMSCRATCH; i++) {
		stv680->scratch[i].data = kmalloc (stv680->rawbufsize, GFP_KERNEL);
		if (stv680->scratch[i].data == NULL) {
			PDEBUG (0, "STV(e): Could not kmalloc raw scratch buffer %i", i);
			goto nomem_err;
		}
		stv680->scratch[i].state = BUFFER_UNUSED;
	}

	for (i = 0; i < STV680_NUMSBUF; i++) {
		urb = usb_alloc_urb (0, GFP_KERNEL);
		if (!urb)
			goto nomem_err;

		/* sbuf is urb->transfer_buffer, later gets memcpyed to scratch */
		usb_fill_bulk_urb (urb, stv680->udev,
				   usb_rcvbulkpipe (stv680->udev, stv680->bulk_in_endpointAddr),
				   stv680->sbuf[i].data, stv680->rawbufsize,
				   stv680_video_irq, stv680);
		stv680->urb[i] = urb;
		err = usb_submit_urb (stv680->urb[i], GFP_KERNEL);
		if (err) {
			PDEBUG (0, "STV(e): urb burned down with err "
				   "%d in start stream %d", err, i);
			goto nomem_err;
		}
	}			/* i STV680_NUMSBUF */

	stv680->framecount = 0;
	return 0;

 nomem_err:
	for (i = 0; i < STV680_NUMSBUF; i++) {
		usb_kill_urb(stv680->urb[i]);
		usb_free_urb(stv680->urb[i]);
		stv680->urb[i] = NULL;
		kfree(stv680->sbuf[i].data);
		stv680->sbuf[i].data = NULL;
	}
	/* used in irq, free only as all URBs are dead */
	for (i = 0; i < STV680_NUMSCRATCH; i++) {
		kfree(stv680->scratch[i].data);
		stv680->scratch[i].data = NULL;
	}
	return -ENOMEM;

}