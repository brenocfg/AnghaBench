#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct drm_radeon_master_private {TYPE_3__* sarea_priv; } ;
struct drm_master {struct drm_radeon_master_private* driver_priv; } ;
struct drm_device {TYPE_1__* agp_buffer_map; TYPE_4__* dev_private; } ;
struct drm_buf {int offset; } ;
struct TYPE_8__ {int offset; int start; int finish; int prim; int vc_format; int numverts; } ;
typedef  TYPE_2__ drm_radeon_tcl_prim_t ;
struct TYPE_9__ {int nbox; int /*<<< orphan*/ * boxes; } ;
typedef  TYPE_3__ drm_radeon_sarea_t ;
struct TYPE_10__ {int gart_buffers_offset; } ;
typedef  TYPE_4__ drm_radeon_private_t ;
struct TYPE_7__ {scalar_t__ handle; } ;

/* Variables and functions */
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  RADEON_3D_RNDR_GEN_INDX_PRIM ; 
 int RADEON_COLOR_ORDER_RGBA ; 
 int RADEON_INDEX_PRIM_OFFSET ; 
 int RADEON_NUM_VERTICES_SHIFT ; 
 int RADEON_PRIM_WALK_IND ; 
 int RADEON_VTX_FMT_RADEON_MODE ; 
 scalar_t__ bad_prim_vertex_nr (int,int) ; 
 int /*<<< orphan*/  radeon_cp_dispatch_indirect (struct drm_device*,struct drm_buf*,int,int) ; 
 int /*<<< orphan*/  radeon_emit_clip_rect (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_cp_dispatch_indices(struct drm_device *dev,
				       struct drm_master *master,
				       struct drm_buf * elt_buf,
				       drm_radeon_tcl_prim_t * prim)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = master->driver_priv;
	drm_radeon_sarea_t *sarea_priv = master_priv->sarea_priv;
	int offset = dev_priv->gart_buffers_offset + prim->offset;
	u32 *data;
	int dwords;
	int i = 0;
	int start = prim->start + RADEON_INDEX_PRIM_OFFSET;
	int count = (prim->finish - start) / sizeof(u16);
	int nbox = sarea_priv->nbox;

	DRM_DEBUG("hwprim 0x%x vfmt 0x%x %d..%d offset: %x nr %d\n",
		  prim->prim,
		  prim->vc_format,
		  prim->start, prim->finish, prim->offset, prim->numverts);

	if (bad_prim_vertex_nr(prim->prim, count)) {
		DRM_ERROR("bad prim %x count %d\n", prim->prim, count);
		return;
	}

	if (start >= prim->finish || (prim->start & 0x7)) {
		DRM_ERROR("buffer prim %d\n", prim->prim);
		return;
	}

	dwords = (prim->finish - prim->start + 3) / sizeof(u32);

	data = (u32 *) ((char *)dev->agp_buffer_map->handle +
			elt_buf->offset + prim->start);

	data[0] = CP_PACKET3(RADEON_3D_RNDR_GEN_INDX_PRIM, dwords - 2);
	data[1] = offset;
	data[2] = prim->numverts;
	data[3] = prim->vc_format;
	data[4] = (prim->prim |
		   RADEON_PRIM_WALK_IND |
		   RADEON_COLOR_ORDER_RGBA |
		   RADEON_VTX_FMT_RADEON_MODE |
		   (count << RADEON_NUM_VERTICES_SHIFT));

	do {
		if (i < nbox)
			radeon_emit_clip_rect(dev_priv, &sarea_priv->boxes[i]);

		radeon_cp_dispatch_indirect(dev, elt_buf,
					    prim->start, prim->finish);

		i++;
	} while (i < nbox);

}