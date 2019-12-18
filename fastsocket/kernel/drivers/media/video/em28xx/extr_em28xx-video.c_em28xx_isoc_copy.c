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
struct urb {int status; int number_of_packets; unsigned char* transfer_buffer; TYPE_2__* iso_frame_desc; } ;
struct em28xx_dmaqueue {scalar_t__ pos; } ;
struct em28xx_buffer {int top_field; int /*<<< orphan*/  vb; } ;
struct TYPE_3__ {struct em28xx_buffer* vid_buf; } ;
struct em28xx {int state; int max_pkt_size; scalar_t__ progressive; TYPE_1__ isoc_ctl; struct em28xx_dmaqueue vidq; } ;
struct TYPE_4__ {int status; int actual_length; int offset; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int ENOENT ; 
 int EPROTO ; 
 int /*<<< orphan*/  buffer_filled (struct em28xx*,struct em28xx_dmaqueue*,struct em28xx_buffer*) ; 
 int /*<<< orphan*/  em28xx_copy_video (struct em28xx*,struct em28xx_dmaqueue*,struct em28xx_buffer*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  em28xx_isocdbg (char*,...) ; 
 int /*<<< orphan*/  get_next_buf (struct em28xx_dmaqueue*,struct em28xx_buffer**) ; 
 int /*<<< orphan*/  print_err_status (struct em28xx*,int,int) ; 
 unsigned char* videobuf_to_vmalloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int em28xx_isoc_copy(struct em28xx *dev, struct urb *urb)
{
	struct em28xx_buffer    *buf;
	struct em28xx_dmaqueue  *dma_q = &dev->vidq;
	unsigned char *outp = NULL;
	int i, len = 0, rc = 1;
	unsigned char *p;

	if (!dev)
		return 0;

	if ((dev->state & DEV_DISCONNECTED) || (dev->state & DEV_MISCONFIGURED))
		return 0;

	if (urb->status < 0) {
		print_err_status(dev, -1, urb->status);
		if (urb->status == -ENOENT)
			return 0;
	}

	buf = dev->isoc_ctl.vid_buf;
	if (buf != NULL)
		outp = videobuf_to_vmalloc(&buf->vb);

	for (i = 0; i < urb->number_of_packets; i++) {
		int status = urb->iso_frame_desc[i].status;

		if (status < 0) {
			print_err_status(dev, i, status);
			if (urb->iso_frame_desc[i].status != -EPROTO)
				continue;
		}

		len = urb->iso_frame_desc[i].actual_length - 4;

		if (urb->iso_frame_desc[i].actual_length <= 0) {
			/* em28xx_isocdbg("packet %d is empty",i); - spammy */
			continue;
		}
		if (urb->iso_frame_desc[i].actual_length >
						dev->max_pkt_size) {
			em28xx_isocdbg("packet bigger than packet size");
			continue;
		}

		p = urb->transfer_buffer + urb->iso_frame_desc[i].offset;

		/* FIXME: incomplete buffer checks where removed to make
		   logic simpler. Impacts of those changes should be evaluated
		 */
		if (p[0] == 0x33 && p[1] == 0x95 && p[2] == 0x00) {
			em28xx_isocdbg("VBI HEADER!!!\n");
			/* FIXME: Should add vbi copy */
			continue;
		}
		if (p[0] == 0x22 && p[1] == 0x5a) {
			em28xx_isocdbg("Video frame %d, length=%i, %s\n", p[2],
				       len, (p[2] & 1) ? "odd" : "even");

			if (dev->progressive || !(p[2] & 1)) {
				if (buf != NULL)
					buffer_filled(dev, dma_q, buf);
				get_next_buf(dma_q, &buf);
				if (buf == NULL)
					outp = NULL;
				else
					outp = videobuf_to_vmalloc(&buf->vb);
			}

			if (buf != NULL) {
				if (p[2] & 1)
					buf->top_field = 0;
				else
					buf->top_field = 1;
			}

			dma_q->pos = 0;
		}
		if (buf != NULL) {
			if (p[0] != 0x88 && p[0] != 0x22) {
				em28xx_isocdbg("frame is not complete\n");
				len += 4;
			} else {
				p += 4;
			}
			em28xx_copy_video(dev, dma_q, buf, p, outp, len);
		}
	}
	return rc;
}