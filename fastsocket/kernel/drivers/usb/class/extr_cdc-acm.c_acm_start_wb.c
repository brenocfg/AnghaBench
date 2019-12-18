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
struct acm_wb {TYPE_1__* urb; int /*<<< orphan*/  len; int /*<<< orphan*/  dmah; int /*<<< orphan*/  buf; } ;
struct acm {int /*<<< orphan*/  dev; int /*<<< orphan*/  transmitting; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  acm_write_done (struct acm*,struct acm_wb*) ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acm_start_wb(struct acm *acm, struct acm_wb *wb)
{
	int rc;

	acm->transmitting++;

	wb->urb->transfer_buffer = wb->buf;
	wb->urb->transfer_dma = wb->dmah;
	wb->urb->transfer_buffer_length = wb->len;
	wb->urb->dev = acm->dev;

	rc = usb_submit_urb(wb->urb, GFP_ATOMIC);
	if (rc < 0) {
		dbg("usb_submit_urb(write bulk) failed: %d", rc);
		acm_write_done(acm, wb);
	}
	return rc;
}