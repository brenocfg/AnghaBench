#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {struct bttv_fh* priv_data; } ;
struct bttv_format {scalar_t__ btformat; unsigned int depth; } ;
struct bttv_fh {int /*<<< orphan*/  do_crop; } ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; scalar_t__ width; scalar_t__ height; } ;
struct bttv_crop {unsigned int min_scaled_width; unsigned int max_scaled_width; unsigned int min_scaled_height; unsigned int max_scaled_height; TYPE_2__ rect; } ;
struct TYPE_7__ {unsigned int bsize; unsigned int size; scalar_t__ baddr; unsigned int width; unsigned int height; int field; scalar_t__ state; } ;
struct bttv_buffer {int tvnorm; TYPE_3__ vb; TYPE_2__ crop; struct bttv_format const* fmt; } ;
struct bttv {int tvnorm; scalar_t__ vbi_end; int /*<<< orphan*/  fbuf; struct bttv_crop* crop; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_5__ {TYPE_2__ defrect; } ;
struct TYPE_8__ {TYPE_1__ cropcap; } ;

/* Variables and functions */
 scalar_t__ BT848_COLOR_FMT_RAW ; 
 int EINVAL ; 
 unsigned int RAW_BPL ; 
 int RAW_LINES ; 
#define  V4L2_FIELD_ALTERNATE 130 
#define  V4L2_FIELD_BOTTOM 129 
#define  V4L2_FIELD_TOP 128 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 int bttv_buffer_risc (struct bttv*,struct bttv_buffer*) ; 
 int /*<<< orphan*/  bttv_dma_free (struct videobuf_queue*,struct bttv*,struct bttv_buffer*) ; 
 TYPE_4__* bttv_tvnorms ; 
 int videobuf_iolock (struct videobuf_queue*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bttv_prepare_buffer(struct videobuf_queue *q,struct bttv *btv,
			       struct bttv_buffer *buf,
			       const struct bttv_format *fmt,
			       unsigned int width, unsigned int height,
			       enum v4l2_field field)
{
	struct bttv_fh *fh = q->priv_data;
	int redo_dma_risc = 0;
	struct bttv_crop c;
	int norm;
	int rc;

	/* check settings */
	if (NULL == fmt)
		return -EINVAL;
	if (fmt->btformat == BT848_COLOR_FMT_RAW) {
		width  = RAW_BPL;
		height = RAW_LINES*2;
		if (width*height > buf->vb.bsize)
			return -EINVAL;
		buf->vb.size = buf->vb.bsize;

		/* Make sure tvnorm and vbi_end remain consistent
		   until we're done. */

		norm = btv->tvnorm;

		/* In this mode capturing always starts at defrect.top
		   (default VDELAY), ignoring cropping parameters. */
		if (btv->vbi_end > bttv_tvnorms[norm].cropcap.defrect.top) {
			return -EINVAL;
		}

		c.rect = bttv_tvnorms[norm].cropcap.defrect;
	} else {
		norm = btv->tvnorm;
		c = btv->crop[!!fh->do_crop];

		if (width < c.min_scaled_width ||
		    width > c.max_scaled_width ||
		    height < c.min_scaled_height)
			return -EINVAL;

		switch (field) {
		case V4L2_FIELD_TOP:
		case V4L2_FIELD_BOTTOM:
		case V4L2_FIELD_ALTERNATE:
			/* btv->crop counts frame lines. Max. scale
			   factor is 16:1 for frames, 8:1 for fields. */
			if (height * 2 > c.max_scaled_height)
				return -EINVAL;
			break;

		default:
			if (height > c.max_scaled_height)
				return -EINVAL;
			break;
		}

		buf->vb.size = (width * height * fmt->depth) >> 3;
		if (0 != buf->vb.baddr  &&  buf->vb.bsize < buf->vb.size)
			return -EINVAL;
	}

	/* alloc + fill struct bttv_buffer (if changed) */
	if (buf->vb.width != width || buf->vb.height != height ||
	    buf->vb.field != field ||
	    buf->tvnorm != norm || buf->fmt != fmt ||
	    buf->crop.top != c.rect.top ||
	    buf->crop.left != c.rect.left ||
	    buf->crop.width != c.rect.width ||
	    buf->crop.height != c.rect.height) {
		buf->vb.width  = width;
		buf->vb.height = height;
		buf->vb.field  = field;
		buf->tvnorm    = norm;
		buf->fmt       = fmt;
		buf->crop      = c.rect;
		redo_dma_risc = 1;
	}

	/* alloc risc memory */
	if (VIDEOBUF_NEEDS_INIT == buf->vb.state) {
		redo_dma_risc = 1;
		if (0 != (rc = videobuf_iolock(q,&buf->vb,&btv->fbuf)))
			goto fail;
	}

	if (redo_dma_risc)
		if (0 != (rc = bttv_buffer_risc(btv,buf)))
			goto fail;

	buf->vb.state = VIDEOBUF_PREPARED;
	return 0;

 fail:
	bttv_dma_free(q,btv,buf);
	return rc;
}