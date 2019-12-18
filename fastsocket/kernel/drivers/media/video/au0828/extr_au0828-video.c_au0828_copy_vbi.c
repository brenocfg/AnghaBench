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
struct au0828_dmaqueue {unsigned long pos; } ;
struct au0828_dev {int vbi_width; int vbi_height; } ;
struct TYPE_2__ {unsigned long size; } ;
struct au0828_buffer {scalar_t__ top_field; TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_isocdbg (char*) ; 

__attribute__((used)) static void au0828_copy_vbi(struct au0828_dev *dev,
			      struct au0828_dmaqueue  *dma_q,
			      struct au0828_buffer *buf,
			      unsigned char *p,
			      unsigned char *outp, unsigned long len)
{
	unsigned char *startwrite, *startread;
	int bytesperline;
	int i, j = 0;

	if (dev == NULL) {
		au0828_isocdbg("dev is null\n");
		return;
	}

	if (dma_q == NULL) {
		au0828_isocdbg("dma_q is null\n");
		return;
	}
	if (buf == NULL)
		return;
	if (p == NULL) {
		au0828_isocdbg("p is null\n");
		return;
	}
	if (outp == NULL) {
		au0828_isocdbg("outp is null\n");
		return;
	}

	bytesperline = dev->vbi_width;

	if (dma_q->pos + len > buf->vb.size)
		len = buf->vb.size - dma_q->pos;

	startread = p;
	startwrite = outp + (dma_q->pos / 2);

	/* Make sure the bottom field populates the second half of the frame */
	if (buf->top_field == 0)
		startwrite += bytesperline * dev->vbi_height;

	for (i = 0; i < len; i += 2)
		startwrite[j++] = startread[i+1];

	dma_q->pos += len;
}