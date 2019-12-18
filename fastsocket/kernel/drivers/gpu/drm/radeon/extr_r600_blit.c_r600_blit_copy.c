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
typedef  int uint64_t ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_10__ {scalar_t__ gart_buffers_offset; TYPE_1__* blit_vb; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_9__ {scalar_t__ used; scalar_t__ total; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_8 ; 
 int /*<<< orphan*/  COLOR_8_8_8_8 ; 
 int /*<<< orphan*/  FMT_8 ; 
 int /*<<< orphan*/  FMT_8_8_8_8 ; 
 int R600_CB0_DEST_BASE_ENA ; 
 int R600_CB_ACTION_ENA ; 
 int R600_TC_ACTION_ENA ; 
 int /*<<< orphan*/  cp_set_surface_sync (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  draw_auto (TYPE_2__*) ; 
 int /*<<< orphan*/  int2float (int) ; 
 int /*<<< orphan*/  r600_nomm_get_vb (struct drm_device*) ; 
 int /*<<< orphan*/ * r600_nomm_get_vb_ptr (struct drm_device*) ; 
 int /*<<< orphan*/  r600_nomm_put_vb (struct drm_device*) ; 
 int /*<<< orphan*/  set_render_target (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  set_scissors (TYPE_2__*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_shaders (struct drm_device*) ; 
 int /*<<< orphan*/  set_tex_resource (TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  set_vtx_resource (TYPE_2__*,scalar_t__) ; 

void
r600_blit_copy(struct drm_device *dev,
	       uint64_t src_gpu_addr, uint64_t dst_gpu_addr,
	       int size_bytes)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	int max_bytes;
	u64 vb_addr;
	u32 *vb;

	vb = r600_nomm_get_vb_ptr(dev);

	if ((size_bytes & 3) || (src_gpu_addr & 3) || (dst_gpu_addr & 3)) {
		max_bytes = 8192;

		while (size_bytes) {
			int cur_size = size_bytes;
			int src_x = src_gpu_addr & 255;
			int dst_x = dst_gpu_addr & 255;
			int h = 1;
			src_gpu_addr = src_gpu_addr & ~255;
			dst_gpu_addr = dst_gpu_addr & ~255;

			if (!src_x && !dst_x) {
				h = (cur_size / max_bytes);
				if (h > 8192)
					h = 8192;
				if (h == 0)
					h = 1;
				else
					cur_size = max_bytes;
			} else {
				if (cur_size > max_bytes)
					cur_size = max_bytes;
				if (cur_size > (max_bytes - dst_x))
					cur_size = (max_bytes - dst_x);
				if (cur_size > (max_bytes - src_x))
					cur_size = (max_bytes - src_x);
			}

			if ((dev_priv->blit_vb->used + 48) > dev_priv->blit_vb->total) {

				r600_nomm_put_vb(dev);
				r600_nomm_get_vb(dev);
				if (!dev_priv->blit_vb)
					return;
				set_shaders(dev);
				vb = r600_nomm_get_vb_ptr(dev);
			}

			vb[0] = int2float(dst_x);
			vb[1] = 0;
			vb[2] = int2float(src_x);
			vb[3] = 0;

			vb[4] = int2float(dst_x);
			vb[5] = int2float(h);
			vb[6] = int2float(src_x);
			vb[7] = int2float(h);

			vb[8] = int2float(dst_x + cur_size);
			vb[9] = int2float(h);
			vb[10] = int2float(src_x + cur_size);
			vb[11] = int2float(h);

			/* src */
			set_tex_resource(dev_priv, FMT_8,
					 src_x + cur_size, h, src_x + cur_size,
					 src_gpu_addr);

			cp_set_surface_sync(dev_priv,
					    R600_TC_ACTION_ENA, (src_x + cur_size * h), src_gpu_addr);

			/* dst */
			set_render_target(dev_priv, COLOR_8,
					  dst_x + cur_size, h,
					  dst_gpu_addr);

			/* scissors */
			set_scissors(dev_priv, dst_x, 0, dst_x + cur_size, h);

			/* Vertex buffer setup */
			vb_addr = dev_priv->gart_buffers_offset +
				dev_priv->blit_vb->offset +
				dev_priv->blit_vb->used;
			set_vtx_resource(dev_priv, vb_addr);

			/* draw */
			draw_auto(dev_priv);

			cp_set_surface_sync(dev_priv,
					    R600_CB_ACTION_ENA | R600_CB0_DEST_BASE_ENA,
					    cur_size * h, dst_gpu_addr);

			vb += 12;
			dev_priv->blit_vb->used += 12 * 4;

			src_gpu_addr += cur_size * h;
			dst_gpu_addr += cur_size * h;
			size_bytes -= cur_size * h;
		}
	} else {
		max_bytes = 8192 * 4;

		while (size_bytes) {
			int cur_size = size_bytes;
			int src_x = (src_gpu_addr & 255);
			int dst_x = (dst_gpu_addr & 255);
			int h = 1;
			src_gpu_addr = src_gpu_addr & ~255;
			dst_gpu_addr = dst_gpu_addr & ~255;

			if (!src_x && !dst_x) {
				h = (cur_size / max_bytes);
				if (h > 8192)
					h = 8192;
				if (h == 0)
					h = 1;
				else
					cur_size = max_bytes;
			} else {
				if (cur_size > max_bytes)
					cur_size = max_bytes;
				if (cur_size > (max_bytes - dst_x))
					cur_size = (max_bytes - dst_x);
				if (cur_size > (max_bytes - src_x))
					cur_size = (max_bytes - src_x);
			}

			if ((dev_priv->blit_vb->used + 48) > dev_priv->blit_vb->total) {
				r600_nomm_put_vb(dev);
				r600_nomm_get_vb(dev);
				if (!dev_priv->blit_vb)
					return;

				set_shaders(dev);
				vb = r600_nomm_get_vb_ptr(dev);
			}

			vb[0] = int2float(dst_x / 4);
			vb[1] = 0;
			vb[2] = int2float(src_x / 4);
			vb[3] = 0;

			vb[4] = int2float(dst_x / 4);
			vb[5] = int2float(h);
			vb[6] = int2float(src_x / 4);
			vb[7] = int2float(h);

			vb[8] = int2float((dst_x + cur_size) / 4);
			vb[9] = int2float(h);
			vb[10] = int2float((src_x + cur_size) / 4);
			vb[11] = int2float(h);

			/* src */
			set_tex_resource(dev_priv, FMT_8_8_8_8,
					 (src_x + cur_size) / 4,
					 h, (src_x + cur_size) / 4,
					 src_gpu_addr);

			cp_set_surface_sync(dev_priv,
					    R600_TC_ACTION_ENA, (src_x + cur_size * h), src_gpu_addr);

			/* dst */
			set_render_target(dev_priv, COLOR_8_8_8_8,
					  (dst_x + cur_size) / 4, h,
					  dst_gpu_addr);

			/* scissors */
			set_scissors(dev_priv, (dst_x / 4), 0, (dst_x + cur_size / 4), h);

			/* Vertex buffer setup */
			vb_addr = dev_priv->gart_buffers_offset +
				dev_priv->blit_vb->offset +
				dev_priv->blit_vb->used;
			set_vtx_resource(dev_priv, vb_addr);

			/* draw */
			draw_auto(dev_priv);

			cp_set_surface_sync(dev_priv,
					    R600_CB_ACTION_ENA | R600_CB0_DEST_BASE_ENA,
					    cur_size * h, dst_gpu_addr);

			vb += 12;
			dev_priv->blit_vb->used += 12 * 4;

			src_gpu_addr += cur_size * h;
			dst_gpu_addr += cur_size * h;
			size_bytes -= cur_size * h;
		}
	}
}