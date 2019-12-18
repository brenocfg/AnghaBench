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
struct TYPE_4__ {int /*<<< orphan*/  iso_skip_count; int /*<<< orphan*/  iso_err_count; } ;
struct uvd {int debug; int /*<<< orphan*/  dp; TYPE_2__ stats; } ;
struct urb {int number_of_packets; char* transfer_buffer; TYPE_1__* iso_frame_desc; } ;
struct TYPE_3__ {int actual_length; int status; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  RingQueue_Enqueue (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  err (char*,int,int,int) ; 

__attribute__((used)) static int usbvideo_CompressIsochronous(struct uvd *uvd, struct urb *urb)
{
	char *cdata;
	int i, totlen = 0;

	for (i = 0; i < urb->number_of_packets; i++) {
		int n = urb->iso_frame_desc[i].actual_length;
		int st = urb->iso_frame_desc[i].status;

		cdata = urb->transfer_buffer + urb->iso_frame_desc[i].offset;

		/* Detect and ignore errored packets */
		if (st < 0) {
			if (uvd->debug >= 1)
				err("Data error: packet=%d. len=%d. status=%d.", i, n, st);
			uvd->stats.iso_err_count++;
			continue;
		}

		/* Detect and ignore empty packets */
		if (n <= 0) {
			uvd->stats.iso_skip_count++;
			continue;
		}
		totlen += n;	/* Little local accounting */
		RingQueue_Enqueue(&uvd->dp, cdata, n);
	}
	return totlen;
}