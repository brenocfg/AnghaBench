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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct cx231xx_dmaqueue {int bytes_left_in_line; int lines_completed; int current_field; int lines_per_field; } ;
struct cx231xx_buffer {int /*<<< orphan*/  vb; } ;
struct TYPE_3__ {struct cx231xx_buffer* buf; } ;
struct TYPE_4__ {TYPE_1__ bulk_ctl; } ;
struct cx231xx {int width; TYPE_2__ vbi_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * videobuf_to_vmalloc (int /*<<< orphan*/ *) ; 

int cx231xx_do_vbi_copy(struct cx231xx *dev, struct cx231xx_dmaqueue *dma_q,
			u8 *p_buffer, u32 bytes_to_copy)
{
	u8 *p_out_buffer = NULL;
	u32 current_line_bytes_copied = 0;
	struct cx231xx_buffer *buf;
	u32 _line_size = dev->width << 1;
	void *startwrite;
	int offset, lencopy;

	buf = dev->vbi_mode.bulk_ctl.buf;

	if (buf == NULL)
		return -EINVAL;

	p_out_buffer = videobuf_to_vmalloc(&buf->vb);

	if (dma_q->bytes_left_in_line != _line_size) {
		current_line_bytes_copied =
		    _line_size - dma_q->bytes_left_in_line;
	}

	offset = (dma_q->lines_completed * _line_size) +
		 current_line_bytes_copied;

	if (dma_q->current_field == 2) {
		/* Populate the second half of the frame */
		offset += (dev->width * 2 * dma_q->lines_per_field);
	}

	/* prepare destination address */
	startwrite = p_out_buffer + offset;

	lencopy = dma_q->bytes_left_in_line > bytes_to_copy ?
		  bytes_to_copy : dma_q->bytes_left_in_line;

	memcpy(startwrite, p_buffer, lencopy);

	return 0;
}