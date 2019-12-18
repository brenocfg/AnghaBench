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
struct TYPE_6__ {int /*<<< orphan*/  iso_err_count; } ;
struct uvd {TYPE_3__ stats; TYPE_2__* dev; } ;
struct urb {int number_of_packets; unsigned char* transfer_buffer; TYPE_1__* iso_frame_desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int actual_length; int status; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int,int) ; 
 scalar_t__ qcm_process_frame (struct uvd*,unsigned char*,int) ; 

__attribute__((used)) static int qcm_compress_iso(struct uvd *uvd, struct urb *dataurb)
{
	int totlen;
	int i;
	unsigned char *cdata;

	totlen=0;
	for (i = 0; i < dataurb->number_of_packets; i++) {
		int n = dataurb->iso_frame_desc[i].actual_length;
		int st = dataurb->iso_frame_desc[i].status;

		cdata = dataurb->transfer_buffer +
			dataurb->iso_frame_desc[i].offset;

		if (st < 0) {
			dev_warn(&uvd->dev->dev,
				 "Data error: packet=%d. len=%d. status=%d.\n",
				 i, n, st);
			uvd->stats.iso_err_count++;
			continue;
		}
		if (!n)
			continue;

		totlen += qcm_process_frame(uvd, cdata, n);
	}
	return totlen;
}