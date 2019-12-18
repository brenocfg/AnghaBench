#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_10__ {scalar_t__ gart_buffers_offset; TYPE_1__* blit_vb; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_9__ {scalar_t__ used; scalar_t__ total; scalar_t__ offset; } ;

/* Variables and functions */
 int COLOR_5_6_5 ; 
 int COLOR_8 ; 
 int COLOR_8_8_8_8 ; 
 int FMT_5_6_5 ; 
 int FMT_8 ; 
 int FMT_8_8_8_8 ; 
 int R600_CB0_DEST_BASE_ENA ; 
 int R600_CB_ACTION_ENA ; 
 int R600_TC_ACTION_ENA ; 
 int /*<<< orphan*/  cp_set_surface_sync (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_auto (TYPE_2__*) ; 
 int /*<<< orphan*/  int2float (int) ; 
 int /*<<< orphan*/  r600_nomm_get_vb (struct drm_device*) ; 
 int /*<<< orphan*/ * r600_nomm_get_vb_ptr (struct drm_device*) ; 
 int /*<<< orphan*/  r600_nomm_put_vb (struct drm_device*) ; 
 int /*<<< orphan*/  set_render_target (TYPE_2__*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_scissors (TYPE_2__*,int,int,int,int) ; 
 int /*<<< orphan*/  set_shaders (struct drm_device*) ; 
 int /*<<< orphan*/  set_tex_resource (TYPE_2__*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_vtx_resource (TYPE_2__*,scalar_t__) ; 

void
r600_blit_swap(struct drm_device *dev,
	       uint64_t src_gpu_addr, uint64_t dst_gpu_addr,
	       int sx, int sy, int dx, int dy,
	       int w, int h, int src_pitch, int dst_pitch, int cpp)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	int cb_format, tex_format;
	int sx2, sy2, dx2, dy2;
	u64 vb_addr;
	u32 *vb;

	if ((dev_priv->blit_vb->used + 48) > dev_priv->blit_vb->total) {

		r600_nomm_put_vb(dev);
		r600_nomm_get_vb(dev);
		if (!dev_priv->blit_vb)
			return;

		set_shaders(dev);
	}
	vb = r600_nomm_get_vb_ptr(dev);

	sx2 = sx + w;
	sy2 = sy + h;
	dx2 = dx + w;
	dy2 = dy + h;

	vb[0] = int2float(dx);
	vb[1] = int2float(dy);
	vb[2] = int2float(sx);
	vb[3] = int2float(sy);

	vb[4] = int2float(dx);
	vb[5] = int2float(dy2);
	vb[6] = int2float(sx);
	vb[7] = int2float(sy2);

	vb[8] = int2float(dx2);
	vb[9] = int2float(dy2);
	vb[10] = int2float(sx2);
	vb[11] = int2float(sy2);

	switch(cpp) {
	case 4:
		cb_format = COLOR_8_8_8_8;
		tex_format = FMT_8_8_8_8;
		break;
	case 2:
		cb_format = COLOR_5_6_5;
		tex_format = FMT_5_6_5;
		break;
	default:
		cb_format = COLOR_8;
		tex_format = FMT_8;
		break;
	}

	/* src */
	set_tex_resource(dev_priv, tex_format,
			 src_pitch / cpp,
			 sy2, src_pitch / cpp,
			 src_gpu_addr);

	cp_set_surface_sync(dev_priv,
			    R600_TC_ACTION_ENA, src_pitch * sy2, src_gpu_addr);

	/* dst */
	set_render_target(dev_priv, cb_format,
			  dst_pitch / cpp, dy2,
			  dst_gpu_addr);

	/* scissors */
	set_scissors(dev_priv, dx, dy, dx2, dy2);

	/* Vertex buffer setup */
	vb_addr = dev_priv->gart_buffers_offset +
		dev_priv->blit_vb->offset +
		dev_priv->blit_vb->used;
	set_vtx_resource(dev_priv, vb_addr);

	/* draw */
	draw_auto(dev_priv);

	cp_set_surface_sync(dev_priv,
			    R600_CB_ACTION_ENA | R600_CB0_DEST_BASE_ENA,
			    dst_pitch * dy2, dst_gpu_addr);

	dev_priv->blit_vb->used += 12 * 4;
}