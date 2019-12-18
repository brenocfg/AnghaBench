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
typedef  int u8 ;
typedef  int u32 ;
struct urb {int status; int number_of_packets; unsigned char* transfer_buffer; TYPE_3__* iso_frame_desc; struct cx231xx_dmaqueue* context; } ;
struct cx231xx_dmaqueue {int last_sav; int /*<<< orphan*/  partial_buf; scalar_t__ is_partial_line; } ;
struct cx231xx_buffer {int /*<<< orphan*/  vb; } ;
struct TYPE_4__ {struct cx231xx_buffer* buf; } ;
struct TYPE_5__ {scalar_t__ max_pkt_size; TYPE_1__ isoc_ctl; } ;
struct cx231xx {int state; TYPE_2__ video_mode; } ;
struct TYPE_6__ {int status; scalar_t__ actual_length; int offset; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int ENOENT ; 
 int EPROTO ; 
 int cx231xx_find_boundary_SAV_EAV (unsigned char*,int /*<<< orphan*/ ,int*) ; 
 int cx231xx_find_next_SAV_EAV (unsigned char*,int,int*) ; 
 int cx231xx_get_video_line (struct cx231xx*,struct cx231xx_dmaqueue*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  cx231xx_isocdbg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  print_err_status (struct cx231xx*,int,int) ; 
 unsigned char* videobuf_to_vmalloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int cx231xx_isoc_copy(struct cx231xx *dev, struct urb *urb)
{
	struct cx231xx_buffer *buf;
	struct cx231xx_dmaqueue *dma_q = urb->context;
	unsigned char *outp = NULL;
	int i, rc = 1;
	unsigned char *p_buffer;
	u32 bytes_parsed = 0, buffer_size = 0;
	u8 sav_eav = 0;

	if (!dev)
		return 0;

	if ((dev->state & DEV_DISCONNECTED) || (dev->state & DEV_MISCONFIGURED))
		return 0;

	if (urb->status < 0) {
		print_err_status(dev, -1, urb->status);
		if (urb->status == -ENOENT)
			return 0;
	}

	buf = dev->video_mode.isoc_ctl.buf;
	if (buf != NULL)
		outp = videobuf_to_vmalloc(&buf->vb);

	for (i = 0; i < urb->number_of_packets; i++) {
		int status = urb->iso_frame_desc[i].status;

		if (status < 0) {
			print_err_status(dev, i, status);
			if (urb->iso_frame_desc[i].status != -EPROTO)
				continue;
		}

		if (urb->iso_frame_desc[i].actual_length <= 0) {
			/* cx231xx_isocdbg("packet %d is empty",i); - spammy */
			continue;
		}
		if (urb->iso_frame_desc[i].actual_length >
		    dev->video_mode.max_pkt_size) {
			cx231xx_isocdbg("packet bigger than packet size");
			continue;
		}

		/*  get buffer pointer and length */
		p_buffer = urb->transfer_buffer + urb->iso_frame_desc[i].offset;
		buffer_size = urb->iso_frame_desc[i].actual_length;
		bytes_parsed = 0;

		if (dma_q->is_partial_line) {
			/* Handle the case of a partial line */
			sav_eav = dma_q->last_sav;
		} else {
			/* Check for a SAV/EAV overlapping
				the buffer boundary */
			sav_eav =
			    cx231xx_find_boundary_SAV_EAV(p_buffer,
							  dma_q->partial_buf,
							  &bytes_parsed);
		}

		sav_eav &= 0xF0;
		/* Get the first line if we have some portion of an SAV/EAV from
		   the last buffer or a partial line  */
		if (sav_eav) {
			bytes_parsed += cx231xx_get_video_line(dev, dma_q,
				sav_eav,	/* SAV/EAV */
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed);/* buf size */
		}

		/* Now parse data that is completely in this buffer */
		/* dma_q->is_partial_line = 0;  */

		while (bytes_parsed < buffer_size) {
			u32 bytes_used = 0;

			sav_eav = cx231xx_find_next_SAV_EAV(
				p_buffer + bytes_parsed,	/* p_buffer */
				buffer_size - bytes_parsed,	/* buf size */
				&bytes_used);/* bytes used to get SAV/EAV */

			bytes_parsed += bytes_used;

			sav_eav &= 0xF0;
			if (sav_eav && (bytes_parsed < buffer_size)) {
				bytes_parsed += cx231xx_get_video_line(dev,
					dma_q, sav_eav,	/* SAV/EAV */
					p_buffer + bytes_parsed,/* p_buffer */
					buffer_size - bytes_parsed);/*buf size*/
			}
		}

		/* Save the last four bytes of the buffer so we can check the
		   buffer boundary condition next time */
		memcpy(dma_q->partial_buf, p_buffer + buffer_size - 4, 4);
		bytes_parsed = 0;

	}
	return rc;
}