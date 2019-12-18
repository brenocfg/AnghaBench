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
struct au0828_dev {int width; int greenscreen_detected; } ;
struct TYPE_2__ {unsigned long size; } ;
struct au0828_buffer {TYPE_1__ vb; scalar_t__ top_field; } ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_isocdbg (char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void au0828_copy_video(struct au0828_dev *dev,
			      struct au0828_dmaqueue  *dma_q,
			      struct au0828_buffer *buf,
			      unsigned char *p,
			      unsigned char *outp, unsigned long len)
{
	void *fieldstart, *startwrite, *startread;
	int  linesdone, currlinedone, offset, lencopy, remain;
	int bytesperline = dev->width << 1; /* Assumes 16-bit depth @@@@ */

	if (len == 0)
		return;

	if (dma_q->pos + len > buf->vb.size)
		len = buf->vb.size - dma_q->pos;

	startread = p;
	remain = len;

	/* Interlaces frame */
	if (buf->top_field)
		fieldstart = outp;
	else
		fieldstart = outp + bytesperline;

	linesdone = dma_q->pos / bytesperline;
	currlinedone = dma_q->pos % bytesperline;
	offset = linesdone * bytesperline * 2 + currlinedone;
	startwrite = fieldstart + offset;
	lencopy = bytesperline - currlinedone;
	lencopy = lencopy > remain ? remain : lencopy;

	if ((char *)startwrite + lencopy > (char *)outp + buf->vb.size) {
		au0828_isocdbg("Overflow of %zi bytes past buffer end (1)\n",
			       ((char *)startwrite + lencopy) -
			       ((char *)outp + buf->vb.size));
		remain = (char *)outp + buf->vb.size - (char *)startwrite;
		lencopy = remain;
	}
	if (lencopy <= 0)
		return;
	memcpy(startwrite, startread, lencopy);

	remain -= lencopy;

	while (remain > 0) {
		startwrite += lencopy + bytesperline;
		startread += lencopy;
		if (bytesperline > remain)
			lencopy = remain;
		else
			lencopy = bytesperline;

		if ((char *)startwrite + lencopy > (char *)outp +
		    buf->vb.size) {
			au0828_isocdbg("Overflow %zi bytes past buf end (2)\n",
				       ((char *)startwrite + lencopy) -
				       ((char *)outp + buf->vb.size));
			lencopy = remain = (char *)outp + buf->vb.size -
					   (char *)startwrite;
		}
		if (lencopy <= 0)
			break;

		memcpy(startwrite, startread, lencopy);

		remain -= lencopy;
	}

	if (offset > 1440) {
		/* We have enough data to check for greenscreen */
		if (outp[0] < 0x60 && outp[1440] < 0x60)
			dev->greenscreen_detected = 1;
	}

	dma_q->pos += len;
}