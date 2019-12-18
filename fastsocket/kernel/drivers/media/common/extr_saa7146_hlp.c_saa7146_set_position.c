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
typedef  void* u32 ;
struct TYPE_6__ {int bytesperline; } ;
struct TYPE_7__ {scalar_t__ base; TYPE_2__ fmt; } ;
struct saa7146_vv {scalar_t__ vflip; TYPE_4__* standard; TYPE_3__ ov_fb; TYPE_1__* ov_fmt; } ;
struct saa7146_video_dma {int pitch; scalar_t__ num_line_byte; int /*<<< orphan*/  base_page; void* prot_addr; void* base_even; void* base_odd; } ;
struct saa7146_format {int /*<<< orphan*/  swap; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_8__ {int v_field; scalar_t__ h_pixels; } ;
struct TYPE_5__ {int depth; } ;

/* Variables and functions */
 int V4L2_FIELD_ALTERNATE ; 
 int V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (int) ; 
 int V4L2_FIELD_TOP ; 
 struct saa7146_format* saa7146_format_by_fourcc (struct saa7146_dev*,void*) ; 
 int /*<<< orphan*/  saa7146_write_out_dma (struct saa7146_dev*,int,struct saa7146_video_dma*) ; 

__attribute__((used)) static void saa7146_set_position(struct saa7146_dev *dev, int w_x, int w_y, int w_height, enum v4l2_field field, u32 pixelformat)
{
	struct saa7146_vv *vv = dev->vv_data;
	struct saa7146_format *sfmt = saa7146_format_by_fourcc(dev, pixelformat);

	int b_depth = vv->ov_fmt->depth;
	int b_bpl = vv->ov_fb.fmt.bytesperline;
	/* The unsigned long cast is to remove a 64-bit compile warning since
	   it looks like a 64-bit address is cast to a 32-bit value, even
	   though the base pointer is really a 32-bit physical address that
	   goes into a 32-bit DMA register.
	   FIXME: might not work on some 64-bit platforms, but see the FIXME
	   in struct v4l2_framebuffer (videodev2.h) for that.
	 */
	u32 base = (u32)(unsigned long)vv->ov_fb.base;

	struct	saa7146_video_dma vdma1;

	/* calculate memory offsets for picture, look if we shall top-down-flip */
	vdma1.pitch	= 2*b_bpl;
	if ( 0 == vv->vflip ) {
		vdma1.base_even = base + (w_y * (vdma1.pitch/2)) + (w_x * (b_depth / 8));
		vdma1.base_odd  = vdma1.base_even + (vdma1.pitch / 2);
		vdma1.prot_addr = vdma1.base_even + (w_height * (vdma1.pitch / 2));
	}
	else {
		vdma1.base_even = base + ((w_y+w_height) * (vdma1.pitch/2)) + (w_x * (b_depth / 8));
		vdma1.base_odd  = vdma1.base_even - (vdma1.pitch / 2);
		vdma1.prot_addr = vdma1.base_odd - (w_height * (vdma1.pitch / 2));
	}

	if (V4L2_FIELD_HAS_BOTH(field)) {
	} else if (field == V4L2_FIELD_ALTERNATE) {
		/* fixme */
		vdma1.base_odd = vdma1.prot_addr;
		vdma1.pitch /= 2;
	} else if (field == V4L2_FIELD_TOP) {
		vdma1.base_odd = vdma1.prot_addr;
		vdma1.pitch /= 2;
	} else if (field == V4L2_FIELD_BOTTOM) {
		vdma1.base_odd = vdma1.base_even;
		vdma1.base_even = vdma1.prot_addr;
		vdma1.pitch /= 2;
	}

	if ( 0 != vv->vflip ) {
		vdma1.pitch *= -1;
	}

	vdma1.base_page = sfmt->swap;
	vdma1.num_line_byte = (vv->standard->v_field<<16)+vv->standard->h_pixels;

	saa7146_write_out_dma(dev, 1, &vdma1);
}