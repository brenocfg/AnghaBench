#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_file {int dummy; } ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_8__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ drm_radeon_kcmd_buffer_t ;
struct TYPE_7__ {scalar_t__ packet_id; } ;
struct TYPE_9__ {TYPE_1__ packet; } ;
typedef  TYPE_3__ drm_radeon_cmd_header_t ;
struct TYPE_10__ {int len; int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CP_PACKET0 (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int RADEON_MAX_STATE_PACKETS ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int drm_buffer_unprocessed (int /*<<< orphan*/ ) ; 
 TYPE_6__* packet ; 
 scalar_t__ radeon_check_and_fixup_packets (int /*<<< orphan*/ *,struct drm_file*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_emit_packets(drm_radeon_private_t * dev_priv,
			       struct drm_file *file_priv,
			       drm_radeon_cmd_header_t header,
			       drm_radeon_kcmd_buffer_t *cmdbuf)
{
	int id = (int)header.packet.packet_id;
	int sz, reg;
	RING_LOCALS;

	if (id >= RADEON_MAX_STATE_PACKETS)
		return -EINVAL;

	sz = packet[id].len;
	reg = packet[id].start;

	if (sz * sizeof(u32) > drm_buffer_unprocessed(cmdbuf->buffer)) {
		DRM_ERROR("Packet size provided larger than data provided\n");
		return -EINVAL;
	}

	if (radeon_check_and_fixup_packets(dev_priv, file_priv, id,
				cmdbuf->buffer)) {
		DRM_ERROR("Packet verification failed\n");
		return -EINVAL;
	}

	BEGIN_RING(sz + 1);
	OUT_RING(CP_PACKET0(reg, (sz - 1)));
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, sz);
	ADVANCE_RING();

	return 0;
}