#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ drm_radeon_kcmd_buffer_t ;
struct TYPE_6__ {int count; int reghi; int reglo; } ;
struct TYPE_8__ {TYPE_1__ packet0; } ;
typedef  TYPE_3__ drm_r300_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CP_PACKET0 (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINVAL ; 
#define  MARK_CHECK_OFFSET 129 
#define  MARK_SAFE 128 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/ * drm_buffer_pointer_to_dword (int /*<<< orphan*/ ,int) ; 
 int* r300_reg_flags ; 
 int /*<<< orphan*/  radeon_check_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int r300_emit_carefully_checked_packet0(drm_radeon_private_t *
							  dev_priv,
							  drm_radeon_kcmd_buffer_t
							  * cmdbuf,
							  drm_r300_cmd_header_t
							  header)
{
	int reg;
	int sz;
	int i;
	u32 *value;
	RING_LOCALS;

	sz = header.packet0.count;
	reg = (header.packet0.reghi << 8) | header.packet0.reglo;

	if ((sz > 64) || (sz < 0)) {
		DRM_ERROR("Cannot emit more than 64 values at a time (reg=%04x sz=%d)\n",
			 reg, sz);
		return -EINVAL;
	}

	for (i = 0; i < sz; i++) {
		switch (r300_reg_flags[(reg >> 2) + i]) {
		case MARK_SAFE:
			break;
		case MARK_CHECK_OFFSET:
			value = drm_buffer_pointer_to_dword(cmdbuf->buffer, i);
			if (!radeon_check_offset(dev_priv, *value)) {
				DRM_ERROR("Offset failed range check (reg=%04x sz=%d)\n",
					 reg, sz);
				return -EINVAL;
			}
			break;
		default:
			DRM_ERROR("Register %04x failed check as flag=%02x\n",
				reg + i * 4, r300_reg_flags[(reg >> 2) + i]);
			return -EINVAL;
		}
	}

	BEGIN_RING(1 + sz);
	OUT_RING(CP_PACKET0(reg, sz - 1));
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, sz);
	ADVANCE_RING();

	return 0;
}