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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {scalar_t__ data; int width; int height; } ;
struct vc_data {TYPE_3__ vc_font; } ;
struct fbcon_ops {scalar_t__ fontdata; scalar_t__ cur_rotate; int rotate; int fd_size; int /*<<< orphan*/ * fontbuffer; TYPE_1__* p; } ;
struct fb_info {TYPE_2__* fbops; struct fbcon_ops* fbcon_par; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fb_sync ) (struct fb_info*) ;} ;
struct TYPE_4__ {scalar_t__ con_rotate; int /*<<< orphan*/  userfont; } ;

/* Variables and functions */
 int ENOMEM ; 
#define  FB_ROTATE_CCW 130 
#define  FB_ROTATE_CW 129 
#define  FB_ROTATE_UD 128 
 int FNTCHARCNT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rotate_ccw (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rotate_cw (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rotate_ud (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 

__attribute__((used)) static int fbcon_rotate_font(struct fb_info *info, struct vc_data *vc)
{
	struct fbcon_ops *ops = info->fbcon_par;
	int len, err = 0;
	int s_cellsize, d_cellsize, i;
	const u8 *src;
	u8 *dst;

	if (vc->vc_font.data == ops->fontdata &&
	    ops->p->con_rotate == ops->cur_rotate)
		goto finished;

	src = ops->fontdata = vc->vc_font.data;
	ops->cur_rotate = ops->p->con_rotate;
	len = (!ops->p->userfont) ? 256 : FNTCHARCNT(src);
	s_cellsize = ((vc->vc_font.width + 7)/8) *
		vc->vc_font.height;
	d_cellsize = s_cellsize;

	if (ops->rotate == FB_ROTATE_CW ||
	    ops->rotate == FB_ROTATE_CCW)
		d_cellsize = ((vc->vc_font.height + 7)/8) *
			vc->vc_font.width;

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	if (ops->fd_size < d_cellsize * len) {
		dst = kmalloc(d_cellsize * len, GFP_KERNEL);

		if (dst == NULL) {
			err = -ENOMEM;
			goto finished;
		}

		ops->fd_size = d_cellsize * len;
		kfree(ops->fontbuffer);
		ops->fontbuffer = dst;
	}

	dst = ops->fontbuffer;
	memset(dst, 0, ops->fd_size);

	switch (ops->rotate) {
	case FB_ROTATE_UD:
		for (i = len; i--; ) {
			rotate_ud(src, dst, vc->vc_font.width,
				  vc->vc_font.height);

			src += s_cellsize;
			dst += d_cellsize;
		}
		break;
	case FB_ROTATE_CW:
		for (i = len; i--; ) {
			rotate_cw(src, dst, vc->vc_font.width,
				  vc->vc_font.height);
			src += s_cellsize;
			dst += d_cellsize;
		}
		break;
	case FB_ROTATE_CCW:
		for (i = len; i--; ) {
			rotate_ccw(src, dst, vc->vc_font.width,
				   vc->vc_font.height);
			src += s_cellsize;
			dst += d_cellsize;
		}
		break;
	}

finished:
	return err;
}