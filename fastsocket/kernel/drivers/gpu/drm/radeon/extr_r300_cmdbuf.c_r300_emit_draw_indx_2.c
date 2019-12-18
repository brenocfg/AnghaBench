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
typedef  int u32 ;
typedef  int /*<<< orphan*/  stack_header ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ drm_radeon_kcmd_buffer_t ;
struct TYPE_9__ {scalar_t__ packet; } ;
struct TYPE_8__ {scalar_t__ cmd_type; } ;
struct TYPE_11__ {TYPE_2__ packet3; TYPE_1__ header; } ;
typedef  TYPE_4__ drm_r300_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 scalar_t__ R300_CMD_PACKET3 ; 
 scalar_t__ R300_CMD_PACKET3_RAW ; 
 int R300_VAP_VF_CNTL__INDEX_SIZE_32bit ; 
 int /*<<< orphan*/  RADEON_CP_INDX_BUFFER ; 
 int RADEON_CP_PACKET_COUNT_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int* drm_buffer_pointer_to_dword (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* drm_buffer_read_object (int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int drm_buffer_unprocessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_check_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline__ int r300_emit_draw_indx_2(drm_radeon_private_t *dev_priv,
					    drm_radeon_kcmd_buffer_t *cmdbuf)
{
	u32 *cmd = drm_buffer_pointer_to_dword(cmdbuf->buffer, 0);
	u32 *cmd1 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 1);
	int count;
	int expected_count;
	RING_LOCALS;

	count = (*cmd & RADEON_CP_PACKET_COUNT_MASK) >> 16;

	expected_count = *cmd1 >> 16;
	if (!(*cmd1 & R300_VAP_VF_CNTL__INDEX_SIZE_32bit))
		expected_count = (expected_count+1)/2;

	if (count && count != expected_count) {
		DRM_ERROR("3D_DRAW_INDX_2: packet size %i, expected %i\n",
			count, expected_count);
		return -EINVAL;
	}

	BEGIN_RING(count+2);
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, count + 2);
	ADVANCE_RING();

	if (!count) {
		drm_r300_cmd_header_t stack_header, *header;
		u32 *cmd1, *cmd2, *cmd3;

		if (drm_buffer_unprocessed(cmdbuf->buffer)
				< 4*4 + sizeof(stack_header)) {
			DRM_ERROR("3D_DRAW_INDX_2: expect subsequent INDX_BUFFER, but stream is too short.\n");
			return -EINVAL;
		}

		header = drm_buffer_read_object(cmdbuf->buffer,
				sizeof(stack_header), &stack_header);

		cmd = drm_buffer_pointer_to_dword(cmdbuf->buffer, 0);
		cmd1 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 1);
		cmd2 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 2);
		cmd3 = drm_buffer_pointer_to_dword(cmdbuf->buffer, 3);

		if (header->header.cmd_type != R300_CMD_PACKET3 ||
		    header->packet3.packet != R300_CMD_PACKET3_RAW ||
		    *cmd != CP_PACKET3(RADEON_CP_INDX_BUFFER, 2)) {
			DRM_ERROR("3D_DRAW_INDX_2: expect subsequent INDX_BUFFER.\n");
			return -EINVAL;
		}

		if ((*cmd1 & 0x8000ffff) != 0x80000810) {
			DRM_ERROR("Invalid indx_buffer reg address %08X\n",
					*cmd1);
			return -EINVAL;
		}
		if (!radeon_check_offset(dev_priv, *cmd2)) {
			DRM_ERROR("Invalid indx_buffer offset is %08X\n",
					*cmd2);
			return -EINVAL;
		}
		if (*cmd3 != expected_count) {
			DRM_ERROR("INDX_BUFFER: buffer size %i, expected %i\n",
				*cmd3, expected_count);
			return -EINVAL;
		}

		BEGIN_RING(4);
		OUT_RING_DRM_BUFFER(cmdbuf->buffer, 4);
		ADVANCE_RING();
	}

	return 0;
}