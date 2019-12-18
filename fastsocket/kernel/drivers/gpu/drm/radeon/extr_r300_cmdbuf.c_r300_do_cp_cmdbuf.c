#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_30__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_27__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
struct drm_radeon_master_private {TYPE_4__* sarea_priv; } ;
struct drm_file {TYPE_27__* master; } ;
struct drm_device_dma {int buf_count; struct drm_buf** buflist; } ;
struct drm_device {struct drm_device_dma* dma; TYPE_5__* dev_private; } ;
struct drm_buf {int /*<<< orphan*/  pending; struct drm_file* file_priv; } ;
typedef  int /*<<< orphan*/  stack_header ;
struct TYPE_40__ {int flags; } ;
typedef  TYPE_5__ drm_radeon_private_t ;
struct TYPE_41__ {scalar_t__ nbox; TYPE_30__* buffer; } ;
typedef  TYPE_6__ drm_radeon_kcmd_buffer_t ;
struct TYPE_38__ {int cmd_type; } ;
struct TYPE_36__ {int buf_idx; } ;
struct TYPE_34__ {int count; } ;
struct TYPE_42__ {TYPE_3__ header; TYPE_2__ dma; TYPE_1__ delay; } ;
typedef  TYPE_7__ drm_r300_cmd_header_t ;
struct TYPE_39__ {int /*<<< orphan*/  last_dispatch; } ;
struct TYPE_37__ {int /*<<< orphan*/  iterator; } ;
struct TYPE_35__ {struct drm_radeon_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CHIP_RV515 ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
#define  R300_CMD_CP_DELAY 136 
#define  R300_CMD_DMA_DISCARD 135 
#define  R300_CMD_END3D 134 
#define  R300_CMD_PACKET0 133 
#define  R300_CMD_PACKET3 132 
#define  R300_CMD_R500FP 131 
#define  R300_CMD_SCRATCH 130 
#define  R300_CMD_VPU 129 
#define  R300_CMD_WAIT 128 
 scalar_t__ R300_SIMULTANEOUS_CLIPRECTS ; 
 int /*<<< orphan*/  RADEON_CP_PACKET2 ; 
 int /*<<< orphan*/  RADEON_DISPATCH_AGE (int /*<<< orphan*/ ) ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 TYPE_7__* drm_buffer_read_object (TYPE_30__*,int,TYPE_7__*) ; 
 int drm_buffer_unprocessed (TYPE_30__*) ; 
 int /*<<< orphan*/  r300_cmd_wait (TYPE_5__*,TYPE_7__) ; 
 int /*<<< orphan*/  r300_discard_buffer (struct drm_device*,TYPE_27__*,struct drm_buf*) ; 
 int r300_emit_cliprects (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int r300_emit_packet0 (TYPE_5__*,TYPE_6__*,TYPE_7__) ; 
 int r300_emit_packet3 (TYPE_5__*,TYPE_6__*,TYPE_7__) ; 
 int r300_emit_r500fp (TYPE_5__*,TYPE_6__*,TYPE_7__) ; 
 int r300_emit_vpu (TYPE_5__*,TYPE_6__*,TYPE_7__) ; 
 int /*<<< orphan*/  r300_pacify (TYPE_5__*) ; 
 int r300_scratch (TYPE_5__*,TYPE_6__*,TYPE_7__) ; 

int r300_do_cp_cmdbuf(struct drm_device *dev,
		      struct drm_file *file_priv,
		      drm_radeon_kcmd_buffer_t *cmdbuf)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = file_priv->master->driver_priv;
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf *buf = NULL;
	int emit_dispatch_age = 0;
	int ret = 0;

	DRM_DEBUG("\n");

	/* pacify */
	r300_pacify(dev_priv);

	if (cmdbuf->nbox <= R300_SIMULTANEOUS_CLIPRECTS) {
		ret = r300_emit_cliprects(dev_priv, cmdbuf, 0);
		if (ret)
			goto cleanup;
	}

	while (drm_buffer_unprocessed(cmdbuf->buffer)
			>= sizeof(drm_r300_cmd_header_t)) {
		int idx;
		drm_r300_cmd_header_t *header, stack_header;

		header = drm_buffer_read_object(cmdbuf->buffer,
				sizeof(stack_header), &stack_header);

		switch (header->header.cmd_type) {
		case R300_CMD_PACKET0:
			DRM_DEBUG("R300_CMD_PACKET0\n");
			ret = r300_emit_packet0(dev_priv, cmdbuf, *header);
			if (ret) {
				DRM_ERROR("r300_emit_packet0 failed\n");
				goto cleanup;
			}
			break;

		case R300_CMD_VPU:
			DRM_DEBUG("R300_CMD_VPU\n");
			ret = r300_emit_vpu(dev_priv, cmdbuf, *header);
			if (ret) {
				DRM_ERROR("r300_emit_vpu failed\n");
				goto cleanup;
			}
			break;

		case R300_CMD_PACKET3:
			DRM_DEBUG("R300_CMD_PACKET3\n");
			ret = r300_emit_packet3(dev_priv, cmdbuf, *header);
			if (ret) {
				DRM_ERROR("r300_emit_packet3 failed\n");
				goto cleanup;
			}
			break;

		case R300_CMD_END3D:
			DRM_DEBUG("R300_CMD_END3D\n");
			/* TODO:
			   Ideally userspace driver should not need to issue this call,
			   i.e. the drm driver should issue it automatically and prevent
			   lockups.

			   In practice, we do not understand why this call is needed and what
			   it does (except for some vague guesses that it has to do with cache
			   coherence) and so the user space driver does it.

			   Once we are sure which uses prevent lockups the code could be moved
			   into the kernel and the userspace driver will not
			   need to use this command.

			   Note that issuing this command does not hurt anything
			   except, possibly, performance */
			r300_pacify(dev_priv);
			break;

		case R300_CMD_CP_DELAY:
			/* simple enough, we can do it here */
			DRM_DEBUG("R300_CMD_CP_DELAY\n");
			{
				int i;
				RING_LOCALS;

				BEGIN_RING(header->delay.count);
				for (i = 0; i < header->delay.count; i++)
					OUT_RING(RADEON_CP_PACKET2);
				ADVANCE_RING();
			}
			break;

		case R300_CMD_DMA_DISCARD:
			DRM_DEBUG("RADEON_CMD_DMA_DISCARD\n");
			idx = header->dma.buf_idx;
			if (idx < 0 || idx >= dma->buf_count) {
				DRM_ERROR("buffer index %d (of %d max)\n",
					  idx, dma->buf_count - 1);
				ret = -EINVAL;
				goto cleanup;
			}

			buf = dma->buflist[idx];
			if (buf->file_priv != file_priv || buf->pending) {
				DRM_ERROR("bad buffer %p %p %d\n",
					  buf->file_priv, file_priv,
					  buf->pending);
				ret = -EINVAL;
				goto cleanup;
			}

			emit_dispatch_age = 1;
			r300_discard_buffer(dev, file_priv->master, buf);
			break;

		case R300_CMD_WAIT:
			DRM_DEBUG("R300_CMD_WAIT\n");
			r300_cmd_wait(dev_priv, *header);
			break;

		case R300_CMD_SCRATCH:
			DRM_DEBUG("R300_CMD_SCRATCH\n");
			ret = r300_scratch(dev_priv, cmdbuf, *header);
			if (ret) {
				DRM_ERROR("r300_scratch failed\n");
				goto cleanup;
			}
			break;

		case R300_CMD_R500FP:
			if ((dev_priv->flags & RADEON_FAMILY_MASK) < CHIP_RV515) {
				DRM_ERROR("Calling r500 command on r300 card\n");
				ret = -EINVAL;
				goto cleanup;
			}
			DRM_DEBUG("R300_CMD_R500FP\n");
			ret = r300_emit_r500fp(dev_priv, cmdbuf, *header);
			if (ret) {
				DRM_ERROR("r300_emit_r500fp failed\n");
				goto cleanup;
			}
			break;
		default:
			DRM_ERROR("bad cmd_type %i at byte %d\n",
				  header->header.cmd_type,
				  cmdbuf->buffer->iterator - (int)sizeof(*header));
			ret = -EINVAL;
			goto cleanup;
		}
	}

	DRM_DEBUG("END\n");

      cleanup:
	r300_pacify(dev_priv);

	/* We emit the vertex buffer age here, outside the pacifier "brackets"
	 * for two reasons:
	 *  (1) This may coalesce multiple age emissions into a single one and
	 *  (2) more importantly, some chips lock up hard when scratch registers
	 *      are written inside the pacifier bracket.
	 */
	if (emit_dispatch_age) {
		RING_LOCALS;

		/* Emit the vertex buffer age */
		BEGIN_RING(2);
		RADEON_DISPATCH_AGE(master_priv->sarea_priv->last_dispatch);
		ADVANCE_RING();
	}

	COMMIT_RING();

	return ret;
}