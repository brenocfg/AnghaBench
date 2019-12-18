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
struct TYPE_3__ {struct em28xx_buffer* vbi_buf; struct em28xx_buffer* vid_buf; } ;
struct em28xx {int state; int max_pkt_size; int capture_type; int vbi_read; unsigned char cur_field; int vbi_width; int vbi_height; scalar_t__ progressive; TYPE_1__ isoc_ctl; struct em28xx_dmaqueue vbiq; struct em28xx_dmaqueue vidq; } ;
struct TYPE_4__ {int status; int actual_length; int offset; } ;

/* Variables and functions */
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int ENOENT ; 
 int EPROTO ; 
 int /*<<< orphan*/  buffer_filled (struct em28xx*,struct em28xx_dmaqueue*,struct em28xx_buffer*) ; 
 int /*<<< orphan*/  em28xx_copy_vbi (struct em28xx*,struct em28xx_dmaqueue*,struct em28xx_buffer*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  em28xx_copy_video (struct em28xx*,struct em28xx_dmaqueue*,struct em28xx_buffer*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  em28xx_isocdbg (char*,...) ; 
 int /*<<< orphan*/  get_next_buf (struct em28xx_dmaqueue*,struct em28xx_buffer**) ; 
 int /*<<< orphan*/  print_err_status (struct em28xx*,int,int) ; 
 int /*<<< orphan*/  vbi_buffer_filled (struct em28xx*,struct em28xx_dmaqueue*,struct em28xx_buffer*) ; 
 int /*<<< orphan*/  vbi_get_next_buf (struct em28xx_dmaqueue*,struct em28xx_buffer**) ; 
 unsigned char* videobuf_to_vmalloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int em28xx_isoc_copy_vbi(struct em28xx *dev, struct urb *urb)
{
	struct em28xx_buffer    *buf, *vbi_buf;
	struct em28xx_dmaqueue  *dma_q = &dev->vidq;
	struct em28xx_dmaqueue  *vbi_dma_q = &dev->vbiq;
	unsigned char *outp = NULL;
	unsigned char *vbioutp = NULL;
	int i, len = 0, rc = 1;
	unsigned char *p;
	int vbi_size;

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

	vbi_buf = dev->isoc_ctl.vbi_buf;
	if (vbi_buf != NULL)
		vbioutp = videobuf_to_vmalloc(&vbi_buf->vb);

	for (i = 0; i < urb->number_of_packets; i++) {
		int status = urb->iso_frame_desc[i].status;

		if (status < 0) {
			print_err_status(dev, i, status);
			if (urb->iso_frame_desc[i].status != -EPROTO)
				continue;
		}

		len = urb->iso_frame_desc[i].actual_length;
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

		/* capture type 0 = vbi start
		   capture type 1 = video start
		   capture type 2 = video in progress */
		if (p[0] == 0x33 && p[1] == 0x95) {
			dev->capture_type = 0;
			dev->vbi_read = 0;
			em28xx_isocdbg("VBI START HEADER!!!\n");
			dev->cur_field = p[2];
			p += 4;
			len -= 4;
		} else if (p[0] == 0x88 && p[1] == 0x88 &&
			   p[2] == 0x88 && p[3] == 0x88) {
			/* continuation */
			p += 4;
			len -= 4;
		} else if (p[0] == 0x22 && p[1] == 0x5a) {
			/* start video */
			p += 4;
			len -= 4;
		}

		vbi_size = dev->vbi_width * dev->vbi_height;

		if (dev->capture_type == 0) {
			if (dev->vbi_read >= vbi_size) {
				/* We've already read all the VBI data, so
				   treat the rest as video */
				em28xx_isocdbg("dev->vbi_read > vbi_size\n");
			} else if ((dev->vbi_read + len) < vbi_size) {
				/* This entire frame is VBI data */
				if (dev->vbi_read == 0 &&
				    (!(dev->cur_field & 1))) {
					/* Brand new frame */
					if (vbi_buf != NULL)
						vbi_buffer_filled(dev,
								  vbi_dma_q,
								  vbi_buf);
					vbi_get_next_buf(vbi_dma_q, &vbi_buf);
					if (vbi_buf == NULL)
						vbioutp = NULL;
					else
						vbioutp = videobuf_to_vmalloc(
							&vbi_buf->vb);
				}

				if (dev->vbi_read == 0) {
					vbi_dma_q->pos = 0;
					if (vbi_buf != NULL) {
						if (dev->cur_field & 1)
							vbi_buf->top_field = 0;
						else
							vbi_buf->top_field = 1;
					}
				}

				dev->vbi_read += len;
				em28xx_copy_vbi(dev, vbi_dma_q, vbi_buf, p,
						vbioutp, len);
			} else {
				/* Some of this frame is VBI data and some is
				   video data */
				int vbi_data_len = vbi_size - dev->vbi_read;
				dev->vbi_read += vbi_data_len;
				em28xx_copy_vbi(dev, vbi_dma_q, vbi_buf, p,
						vbioutp, vbi_data_len);
				dev->capture_type = 1;
				p += vbi_data_len;
				len -= vbi_data_len;
			}
		}

		if (dev->capture_type == 1) {
			dev->capture_type = 2;
			if (dev->progressive || !(dev->cur_field & 1)) {
				if (buf != NULL)
					buffer_filled(dev, dma_q, buf);
				get_next_buf(dma_q, &buf);
				if (buf == NULL)
					outp = NULL;
				else
					outp = videobuf_to_vmalloc(&buf->vb);
			}
			if (buf != NULL) {
				if (dev->cur_field & 1)
					buf->top_field = 0;
				else
					buf->top_field = 1;
			}

			dma_q->pos = 0;
		}

		if (buf != NULL && dev->capture_type == 2) {
			if (len >= 4 && p[0] == 0x88 && p[1] == 0x88 &&
			    p[2] == 0x88 && p[3] == 0x88) {
				p += 4;
				len -= 4;
			}
			if (len >= 4 && p[0] == 0x22 && p[1] == 0x5a) {
				em28xx_isocdbg("Video frame %d, len=%i, %s\n",
					       p[2], len, (p[2] & 1) ?
					       "odd" : "even");
				p += 4;
				len -= 4;
			}

			if (len > 0)
				em28xx_copy_video(dev, dma_q, buf, p, outp,
						  len);
		}
	}
	return rc;
}