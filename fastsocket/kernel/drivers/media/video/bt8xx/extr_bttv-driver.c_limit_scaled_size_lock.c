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
struct v4l2_rect {unsigned int height; scalar_t__ top; int /*<<< orphan*/  width; } ;
struct bttv_fh {scalar_t__ do_crop; struct bttv* btv; } ;
struct TYPE_5__ {scalar_t__ top; } ;
struct bttv_crop {unsigned int min_scaled_width; unsigned int min_scaled_height; unsigned int max_scaled_width; unsigned int max_scaled_height; TYPE_2__ rect; } ;
struct bttv {size_t tvnorm; scalar_t__ vbi_end; struct bttv_crop* crop; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  unsigned int __s32 ;
struct TYPE_4__ {struct v4l2_rect bounds; } ;
struct TYPE_6__ {TYPE_1__ cropcap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAX_HACTIVE ; 
 int /*<<< orphan*/  V4L2_FIELD_HAS_BOTH (int) ; 
 int /*<<< orphan*/  VIDEO_RESOURCES ; 
 int /*<<< orphan*/  bttv_crop_adjust (struct bttv_crop*,struct v4l2_rect const*,unsigned int,unsigned int,int) ; 
 TYPE_3__* bttv_tvnorms ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  locked_btres (struct bttv*,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
limit_scaled_size_lock       (struct bttv_fh *               fh,
			 __s32 *                        width,
			 __s32 *                        height,
			 enum v4l2_field                field,
			 unsigned int			width_mask,
			 unsigned int			width_bias,
			 int                            adjust_size,
			 int                            adjust_crop)
{
	struct bttv *btv = fh->btv;
	const struct v4l2_rect *b;
	struct bttv_crop *c;
	__s32 min_width;
	__s32 min_height;
	__s32 max_width;
	__s32 max_height;
	int rc;

	BUG_ON((int) width_mask >= 0 ||
	       width_bias >= (unsigned int) -width_mask);

	/* Make sure tvnorm, vbi_end and the current cropping parameters
	   remain consistent until we're done. */

	b = &bttv_tvnorms[btv->tvnorm].cropcap.bounds;

	/* Do crop - use current, don't - use default parameters. */
	c = &btv->crop[!!fh->do_crop];

	if (fh->do_crop
	    && adjust_size
	    && adjust_crop
	    && !locked_btres(btv, VIDEO_RESOURCES)) {
		min_width = 48;
		min_height = 32;

		/* We cannot scale up. When the scaled image is larger
		   than crop.rect we adjust the crop.rect as required
		   by the V4L2 spec, hence cropcap.bounds are our limit. */
		max_width = min(b->width, (__s32) MAX_HACTIVE);
		max_height = b->height;

		/* We cannot capture the same line as video and VBI data.
		   Note btv->vbi_end is really a minimum, see
		   bttv_vbi_try_fmt(). */
		if (btv->vbi_end > b->top) {
			max_height -= btv->vbi_end - b->top;
			rc = -EBUSY;
			if (min_height > max_height)
				goto fail;
		}
	} else {
		rc = -EBUSY;
		if (btv->vbi_end > c->rect.top)
			goto fail;

		min_width  = c->min_scaled_width;
		min_height = c->min_scaled_height;
		max_width  = c->max_scaled_width;
		max_height = c->max_scaled_height;

		adjust_crop = 0;
	}

	min_width = (min_width - width_mask - 1) & width_mask;
	max_width = max_width & width_mask;

	/* Max. scale factor is 16:1 for frames, 8:1 for fields. */
	min_height = min_height;
	/* Min. scale factor is 1:1. */
	max_height >>= !V4L2_FIELD_HAS_BOTH(field);

	if (adjust_size) {
		*width = clamp(*width, min_width, max_width);
		*height = clamp(*height, min_height, max_height);

		/* Round after clamping to avoid overflow. */
		*width = (*width + width_bias) & width_mask;

		if (adjust_crop) {
			bttv_crop_adjust(c, b, *width, *height, field);

			if (btv->vbi_end > c->rect.top) {
				/* Move the crop window out of the way. */
				c->rect.top = btv->vbi_end;
			}
		}
	} else {
		rc = -EINVAL;
		if (*width  < min_width ||
		    *height < min_height ||
		    *width  > max_width ||
		    *height > max_height ||
		    0 != (*width & ~width_mask))
			goto fail;
	}

	rc = 0; /* success */

 fail:

	return rc;
}