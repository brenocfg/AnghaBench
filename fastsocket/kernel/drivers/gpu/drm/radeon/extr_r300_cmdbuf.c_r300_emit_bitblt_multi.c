#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ drm_radeon_kcmd_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int RADEON_CP_PACKET_COUNT_MASK ; 
 int RADEON_GMC_DST_PITCH_OFFSET_CNTL ; 
 int RADEON_GMC_SRC_PITCH_OFFSET_CNTL ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int* drm_buffer_pointer_to_dword (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_check_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline__ int r300_emit_bitblt_multi(drm_radeon_private_t *dev_priv,
					     drm_radeon_kcmd_buffer_t *cmdbuf)
{
	u32 *cmd = drm_buffer_pointer_to_dword(cmdbuf->buffer, 0);
	int count, ret;
	RING_LOCALS;


	count = (*cmd & RADEON_CP_PACKET_COUNT_MASK) >> 16;

	if (*cmd & 0x8000) {
		u32 offset;
		u32 *cmd1 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 1);
		if (*cmd1 & (RADEON_GMC_SRC_PITCH_OFFSET_CNTL
			      | RADEON_GMC_DST_PITCH_OFFSET_CNTL)) {

			u32 *cmd2 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 2);
			offset = *cmd2 << 10;
			ret = !radeon_check_offset(dev_priv, offset);
			if (ret) {
				DRM_ERROR("Invalid bitblt first offset is %08X\n", offset);
				return -EINVAL;
			}
		}

		if ((*cmd1 & RADEON_GMC_SRC_PITCH_OFFSET_CNTL) &&
		    (*cmd1 & RADEON_GMC_DST_PITCH_OFFSET_CNTL)) {
			u32 *cmd3 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 3);
			offset = *cmd3 << 10;
			ret = !radeon_check_offset(dev_priv, offset);
			if (ret) {
				DRM_ERROR("Invalid bitblt second offset is %08X\n", offset);
				return -EINVAL;
			}

		}
	}

	BEGIN_RING(count+2);
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, count + 2);
	ADVANCE_RING();

	return 0;
}