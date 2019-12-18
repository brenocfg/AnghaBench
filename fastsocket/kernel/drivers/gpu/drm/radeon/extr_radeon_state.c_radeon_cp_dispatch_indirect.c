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
typedef  int /*<<< orphan*/  u32 ;
struct drm_device {TYPE_1__* agp_buffer_map; TYPE_2__* dev_private; } ;
struct drm_buf {int offset; int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {int gart_buffers_offset; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_3__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  RADEON_CP_IB_BASE ; 
 int /*<<< orphan*/  RADEON_CP_PACKET2 ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static void radeon_cp_dispatch_indirect(struct drm_device * dev,
					struct drm_buf * buf, int start, int end)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	RING_LOCALS;
	DRM_DEBUG("buf=%d s=0x%x e=0x%x\n", buf->idx, start, end);

	if (start != end) {
		int offset = (dev_priv->gart_buffers_offset
			      + buf->offset + start);
		int dwords = (end - start + 3) / sizeof(u32);

		/* Indirect buffer data must be an even number of
		 * dwords, so if we've been given an odd number we must
		 * pad the data with a Type-2 CP packet.
		 */
		if (dwords & 1) {
			u32 *data = (u32 *)
			    ((char *)dev->agp_buffer_map->handle
			     + buf->offset + start);
			data[dwords++] = RADEON_CP_PACKET2;
		}

		/* Fire off the indirect buffer */
		BEGIN_RING(3);

		OUT_RING(CP_PACKET0(RADEON_CP_IB_BASE, 1));
		OUT_RING(offset);
		OUT_RING(dwords);

		ADVANCE_RING();
	}
}