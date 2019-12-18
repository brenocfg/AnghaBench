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
struct TYPE_3__ {int width; int height; } ;
struct vc_data {TYPE_1__ vc_font; } ;
struct TYPE_4__ {int size; int scan_align; int buf_align; } ;
struct fb_info {TYPE_2__ pixmap; } ;
struct fb_image {int fg_color; int bg_color; int dx; int dy; int height; int depth; int width; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bit_putcs_aligned (struct vc_data*,struct fb_info*,unsigned short const*,int,int,int,int,int,struct fb_image*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bit_putcs_unaligned (struct vc_data*,struct fb_info*,unsigned short const*,int,int,int,int,int,struct fb_image*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fb_get_buffer_offset (struct fb_info*,TYPE_2__*,int) ; 
 int get_attribute (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_readw (unsigned short const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bit_putcs(struct vc_data *vc, struct fb_info *info,
		      const unsigned short *s, int count, int yy, int xx,
		      int fg, int bg)
{
	struct fb_image image;
	u32 width = DIV_ROUND_UP(vc->vc_font.width, 8);
	u32 cellsize = width * vc->vc_font.height;
	u32 maxcnt = info->pixmap.size/cellsize;
	u32 scan_align = info->pixmap.scan_align - 1;
	u32 buf_align = info->pixmap.buf_align - 1;
	u32 mod = vc->vc_font.width % 8, cnt, pitch, size;
	u32 attribute = get_attribute(info, scr_readw(s));
	u8 *dst, *buf = NULL;

	image.fg_color = fg;
	image.bg_color = bg;
	image.dx = xx * vc->vc_font.width;
	image.dy = yy * vc->vc_font.height;
	image.height = vc->vc_font.height;
	image.depth = 1;

	if (attribute) {
		buf = kmalloc(cellsize, GFP_KERNEL);
		if (!buf)
			return;
	}

	while (count) {
		if (count > maxcnt)
			cnt = maxcnt;
		else
			cnt = count;

		image.width = vc->vc_font.width * cnt;
		pitch = DIV_ROUND_UP(image.width, 8) + scan_align;
		pitch &= ~scan_align;
		size = pitch * image.height + buf_align;
		size &= ~buf_align;
		dst = fb_get_buffer_offset(info, &info->pixmap, size);
		image.data = dst;

		if (!mod)
			bit_putcs_aligned(vc, info, s, attribute, cnt, pitch,
					  width, cellsize, &image, buf, dst);
		else
			bit_putcs_unaligned(vc, info, s, attribute, cnt,
					    pitch, width, cellsize, &image,
					    buf, dst);

		image.dx += cnt * vc->vc_font.width;
		count -= cnt;
		s += cnt;
	}

	/* buf is always NULL except when in monochrome mode, so in this case
	   it's a gain to check buf against NULL even though kfree() handles
	   NULL pointers just fine */
	if (unlikely(buf))
		kfree(buf);

}