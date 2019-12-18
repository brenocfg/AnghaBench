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
struct em28xx_buffer {TYPE_1__ vb; scalar_t__ top_field; } ;
struct em28xx {int width; scalar_t__ progressive; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_isocdbg (char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void em28xx_copy_video(struct em28xx *dev,
			      struct em28xx_dmaqueue  *dma_q,
			      struct em28xx_buffer *buf,
			      unsigned char *p,
			      unsigned char *outp, unsigned long len)
{
	void *fieldstart, *startwrite, *startread;
	int  linesdone, currlinedone, offset, lencopy, remain;
	int bytesperline = dev->width << 1;

	if (dma_q->pos + len > buf->vb.size)
		len = buf->vb.size - dma_q->pos;

	startread = p;
	remain = len;

	if (dev->progressive)
		fieldstart = outp;
	else {
		/* Interlaces two half frames */
		if (buf->top_field)
			fieldstart = outp;
		else
			fieldstart = outp + bytesperline;
	}

	linesdone = dma_q->pos / bytesperline;
	currlinedone = dma_q->pos % bytesperline;

	if (dev->progressive)
		offset = linesdone * bytesperline + currlinedone;
	else
		offset = linesdone * bytesperline * 2 + currlinedone;

	startwrite = fieldstart + offset;
	lencopy = bytesperline - currlinedone;
	lencopy = lencopy > remain ? remain : lencopy;

	if ((char *)startwrite + lencopy > (char *)outp + buf->vb.size) {
		em28xx_isocdbg("Overflow of %zi bytes past buffer end (1)\n",
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
			em28xx_isocdbg("Overflow of %zi bytes past buffer end"
				       "(2)\n",
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

	dma_q->pos += len;
}