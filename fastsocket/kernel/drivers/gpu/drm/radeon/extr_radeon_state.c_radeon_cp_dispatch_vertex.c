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
struct drm_radeon_master_private {TYPE_3__* sarea_priv; } ;
struct drm_file {TYPE_1__* master; } ;
struct drm_device {TYPE_4__* dev_private; } ;
struct drm_buf {int offset; } ;
struct TYPE_8__ {int start; int prim; int vc_format; scalar_t__ numverts; int /*<<< orphan*/  finish; } ;
typedef  TYPE_2__ drm_radeon_tcl_prim_t ;
struct TYPE_9__ {int nbox; int /*<<< orphan*/ * boxes; } ;
typedef  TYPE_3__ drm_radeon_sarea_t ;
struct TYPE_10__ {int gart_buffers_offset; } ;
typedef  TYPE_4__ drm_radeon_private_t ;
struct TYPE_7__ {struct drm_radeon_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  RADEON_3D_RNDR_GEN_INDX_PRIM ; 
 int RADEON_COLOR_ORDER_RGBA ; 
 int RADEON_NUM_VERTICES_SHIFT ; 
 int RADEON_PRIM_WALK_LIST ; 
 int RADEON_VTX_FMT_RADEON_MODE ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 scalar_t__ bad_prim_vertex_nr (int,scalar_t__) ; 
 int /*<<< orphan*/  radeon_emit_clip_rect (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_cp_dispatch_vertex(struct drm_device * dev,
				      struct drm_file *file_priv,
				      struct drm_buf * buf,
				      drm_radeon_tcl_prim_t * prim)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = file_priv->master->driver_priv;
	drm_radeon_sarea_t *sarea_priv = master_priv->sarea_priv;
	int offset = dev_priv->gart_buffers_offset + buf->offset + prim->start;
	int numverts = (int)prim->numverts;
	int nbox = sarea_priv->nbox;
	int i = 0;
	RING_LOCALS;

	DRM_DEBUG("hwprim 0x%x vfmt 0x%x %d..%d %d verts\n",
		  prim->prim,
		  prim->vc_format, prim->start, prim->finish, prim->numverts);

	if (bad_prim_vertex_nr(prim->prim, prim->numverts)) {
		DRM_ERROR("bad prim %x numverts %d\n",
			  prim->prim, prim->numverts);
		return;
	}

	do {
		/* Emit the next cliprect */
		if (i < nbox) {
			radeon_emit_clip_rect(dev_priv, &sarea_priv->boxes[i]);
		}

		/* Emit the vertex buffer rendering commands */
		BEGIN_RING(5);

		OUT_RING(CP_PACKET3(RADEON_3D_RNDR_GEN_INDX_PRIM, 3));
		OUT_RING(offset);
		OUT_RING(numverts);
		OUT_RING(prim->vc_format);
		OUT_RING(prim->prim | RADEON_PRIM_WALK_LIST |
			 RADEON_COLOR_ORDER_RGBA |
			 RADEON_VTX_FMT_RADEON_MODE |
			 (numverts << RADEON_NUM_VERTICES_SHIFT));

		ADVANCE_RING();

		i++;
	} while (i < nbox);
}