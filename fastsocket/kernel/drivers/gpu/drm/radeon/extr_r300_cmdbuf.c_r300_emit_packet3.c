#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_12__ {int nbox; TYPE_2__* buffer; } ;
typedef  TYPE_3__ drm_radeon_kcmd_buffer_t ;
struct TYPE_10__ {int packet; } ;
struct TYPE_13__ {TYPE_1__ packet3; } ;
typedef  TYPE_4__ drm_r300_cmd_header_t ;
struct TYPE_11__ {int iterator; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
#define  R300_CMD_PACKET3_CLEAR 129 
#define  R300_CMD_PACKET3_RAW 128 
 int R300_SIMULTANEOUS_CLIPRECTS ; 
 int r300_emit_clear (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int r300_emit_cliprects (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int r300_emit_raw_packet3 (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static __inline__ int r300_emit_packet3(drm_radeon_private_t *dev_priv,
					drm_radeon_kcmd_buffer_t *cmdbuf,
					drm_r300_cmd_header_t header)
{
	int n;
	int ret;
	int orig_iter = cmdbuf->buffer->iterator;

	/* This is a do-while-loop so that we run the interior at least once,
	 * even if cmdbuf->nbox is 0. Compare r300_emit_cliprects for rationale.
	 */
	n = 0;
	do {
		if (cmdbuf->nbox > R300_SIMULTANEOUS_CLIPRECTS) {
			ret = r300_emit_cliprects(dev_priv, cmdbuf, n);
			if (ret)
				return ret;

			cmdbuf->buffer->iterator = orig_iter;
		}

		switch (header.packet3.packet) {
		case R300_CMD_PACKET3_CLEAR:
			DRM_DEBUG("R300_CMD_PACKET3_CLEAR\n");
			ret = r300_emit_clear(dev_priv, cmdbuf);
			if (ret) {
				DRM_ERROR("r300_emit_clear failed\n");
				return ret;
			}
			break;

		case R300_CMD_PACKET3_RAW:
			DRM_DEBUG("R300_CMD_PACKET3_RAW\n");
			ret = r300_emit_raw_packet3(dev_priv, cmdbuf);
			if (ret) {
				DRM_ERROR("r300_emit_raw_packet3 failed\n");
				return ret;
			}
			break;

		default:
			DRM_ERROR("bad packet3 type %i at byte %d\n",
				  header.packet3.packet,
				  cmdbuf->buffer->iterator - (int)sizeof(header));
			return -EINVAL;
		}

		n += R300_SIMULTANEOUS_CLIPRECTS;
	} while (n < cmdbuf->nbox);

	return 0;
}