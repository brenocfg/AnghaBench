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
struct em28xx_dmaqueue {unsigned long pos; } ;
struct TYPE_2__ {unsigned long size; } ;
struct em28xx_buffer {scalar_t__ top_field; TYPE_1__ vb; } ;
struct em28xx {int vbi_width; int vbi_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_isocdbg (char*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 

__attribute__((used)) static void em28xx_copy_vbi(struct em28xx *dev,
			      struct em28xx_dmaqueue  *dma_q,
			      struct em28xx_buffer *buf,
			      unsigned char *p,
			      unsigned char *outp, unsigned long len)
{
	void *startwrite, *startread;
	int  offset;
	int bytesperline;

	if (dev == NULL) {
		em28xx_isocdbg("dev is null\n");
		return;
	}
	bytesperline = dev->vbi_width;

	if (dma_q == NULL) {
		em28xx_isocdbg("dma_q is null\n");
		return;
	}
	if (buf == NULL) {
		return;
	}
	if (p == NULL) {
		em28xx_isocdbg("p is null\n");
		return;
	}
	if (outp == NULL) {
		em28xx_isocdbg("outp is null\n");
		return;
	}

	if (dma_q->pos + len > buf->vb.size)
		len = buf->vb.size - dma_q->pos;

	startread = p;

	startwrite = outp + dma_q->pos;
	offset = dma_q->pos;

	/* Make sure the bottom field populates the second half of the frame */
	if (buf->top_field == 0) {
		startwrite += bytesperline * dev->vbi_height;
		offset += bytesperline * dev->vbi_height;
	}

	memcpy(startwrite, startread, len);
	dma_q->pos += len;
}