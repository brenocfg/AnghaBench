#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  track_flush; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ drm_radeon_kcmd_buffer_t ;
struct TYPE_8__ {int count; int adrhi; int adrlo; } ;
struct TYPE_11__ {TYPE_1__ vpu; } ;
typedef  TYPE_4__ drm_r300_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_PACKET0_TABLE (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R300_RB3D_DC_FLUSH ; 
 int /*<<< orphan*/  R300_RB3D_DSTCACHE_CTLSTAT ; 
 int /*<<< orphan*/  R300_VAP_PVS_STATE_FLUSH_REG ; 
 int /*<<< orphan*/  R300_VAP_PVS_UPLOAD_ADDRESS ; 
 int /*<<< orphan*/  R300_VAP_PVS_UPLOAD_DATA ; 
 int /*<<< orphan*/  RADEON_FLUSH_EMITED ; 
 int /*<<< orphan*/  RADEON_WAIT_3D_IDLECLEAN ; 
 int /*<<< orphan*/  RADEON_WAIT_UNTIL ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int drm_buffer_unprocessed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int r300_emit_vpu(drm_radeon_private_t *dev_priv,
				    drm_radeon_kcmd_buffer_t *cmdbuf,
				    drm_r300_cmd_header_t header)
{
	int sz;
	int addr;
	RING_LOCALS;

	sz = header.vpu.count;
	addr = (header.vpu.adrhi << 8) | header.vpu.adrlo;

	if (!sz)
		return 0;
	if (sz * 16 > drm_buffer_unprocessed(cmdbuf->buffer))
		return -EINVAL;

	/* VAP is very sensitive so we purge cache before we program it
	 * and we also flush its state before & after */
	BEGIN_RING(6);
	OUT_RING(CP_PACKET0(R300_RB3D_DSTCACHE_CTLSTAT, 0));
	OUT_RING(R300_RB3D_DC_FLUSH);
	OUT_RING(CP_PACKET0(RADEON_WAIT_UNTIL, 0));
	OUT_RING(RADEON_WAIT_3D_IDLECLEAN);
	OUT_RING(CP_PACKET0(R300_VAP_PVS_STATE_FLUSH_REG, 0));
	OUT_RING(0);
	ADVANCE_RING();
	/* set flush flag */
	dev_priv->track_flush |= RADEON_FLUSH_EMITED;

	BEGIN_RING(3 + sz * 4);
	OUT_RING_REG(R300_VAP_PVS_UPLOAD_ADDRESS, addr);
	OUT_RING(CP_PACKET0_TABLE(R300_VAP_PVS_UPLOAD_DATA, sz * 4 - 1));
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, sz * 4);
	ADVANCE_RING();

	BEGIN_RING(2);
	OUT_RING(CP_PACKET0(R300_VAP_PVS_STATE_FLUSH_REG, 0));
	OUT_RING(0);
	ADVANCE_RING();

	return 0;
}