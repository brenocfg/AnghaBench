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
struct TYPE_4__ {int /*<<< orphan*/  iso_skip_count; int /*<<< orphan*/  iso_err_count; } ;
struct uvd {int /*<<< orphan*/  dp; TYPE_3__* dev; TYPE_1__ stats; scalar_t__ user_data; } ;
struct urb {unsigned char* transfer_buffer; int number_of_packets; TYPE_2__* iso_frame_desc; } ;
struct konicawc {int buttonsts; int lastframe; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int actual_length; int status; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  RingQueue_Enqueue (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  konicawc_report_buttonstat (struct konicawc*) ; 

__attribute__((used)) static int konicawc_compress_iso(struct uvd *uvd, struct urb *dataurb, struct urb *stsurb)
{
	char *cdata;
	int i, totlen = 0;
	unsigned char *status = stsurb->transfer_buffer;
	int keep = 0, discard = 0, bad = 0;
	struct konicawc *cam = (struct konicawc *)uvd->user_data;

	for (i = 0; i < dataurb->number_of_packets; i++) {
		int button = cam->buttonsts;
		unsigned char sts;
		int n = dataurb->iso_frame_desc[i].actual_length;
		int st = dataurb->iso_frame_desc[i].status;
		cdata = dataurb->transfer_buffer +
			dataurb->iso_frame_desc[i].offset;

		/* Detect and ignore errored packets */
		if (st < 0) {
			DEBUG(1, "Data error: packet=%d. len=%d. status=%d.",
			      i, n, st);
			uvd->stats.iso_err_count++;
			continue;
		}

		/* Detect and ignore empty packets */
		if (n <= 0) {
			uvd->stats.iso_skip_count++;
			continue;
		}

		/* See what the status data said about the packet */
		sts = *(status+stsurb->iso_frame_desc[i].offset);

		/* sts: 0x80-0xff: frame start with frame number (ie 0-7f)
		 * otherwise:
		 * bit 0 0: keep packet
		 *	 1: drop packet (padding data)
		 *
		 * bit 4 0 button not clicked
		 *       1 button clicked
		 * button is used to `take a picture' (in software)
		 */

		if(sts < 0x80) {
			button = !!(sts & 0x40);
			sts &= ~0x40;
		}

		/* work out the button status, but don't do
		   anything with it for now */

		if(button != cam->buttonsts) {
			DEBUG(2, "button: %sclicked", button ? "" : "un");
			cam->buttonsts = button;
			konicawc_report_buttonstat(cam);
		}

		if(sts == 0x01) { /* drop frame */
			discard++;
			continue;
		}

		if((sts > 0x01) && (sts < 0x80)) {
			dev_info(&uvd->dev->dev, "unknown status %2.2x\n",
				 sts);
			bad++;
			continue;
		}
		if(!sts && cam->lastframe == -2) {
			DEBUG(2, "dropping frame looking for image start");
			continue;
		}

		keep++;
		if(sts & 0x80) { /* frame start */
			unsigned char marker[] = { 0, 0xff, 0, 0x00 };

			if(cam->lastframe == -2) {
				DEBUG(2, "found initial image");
				cam->lastframe = -1;
			}

			marker[3] = sts & 0x7F;
			RingQueue_Enqueue(&uvd->dp, marker, 4);
			totlen += 4;
		}

		totlen += n;	/* Little local accounting */
		RingQueue_Enqueue(&uvd->dp, cdata, n);
	}
	DEBUG(8, "finished: keep = %d discard = %d bad = %d added %d bytes",
		    keep, discard, bad, totlen);
	return totlen;
}