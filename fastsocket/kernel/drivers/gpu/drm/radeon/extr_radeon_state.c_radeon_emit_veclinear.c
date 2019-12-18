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
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_7__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ drm_radeon_kcmd_buffer_t ;
struct TYPE_6__ {int count; int addr_lo; int addr_hi; } ;
struct TYPE_8__ {TYPE_1__ veclinear; } ;
typedef  TYPE_3__ drm_radeon_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CP_PACKET0_TABLE (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_SE_TCL_STATE_FLUSH ; 
 int /*<<< orphan*/  RADEON_SE_TCL_VECTOR_DATA_REG ; 
 int /*<<< orphan*/  RADEON_SE_TCL_VECTOR_INDX_REG ; 
 int RADEON_VEC_INDX_OCTWORD_STRIDE_SHIFT ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int drm_buffer_unprocessed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int radeon_emit_veclinear(drm_radeon_private_t *dev_priv,
					  drm_radeon_cmd_header_t header,
					  drm_radeon_kcmd_buffer_t *cmdbuf)
{
	int sz = header.veclinear.count * 4;
	int start = header.veclinear.addr_lo | (header.veclinear.addr_hi << 8);
	RING_LOCALS;

        if (!sz)
                return 0;
	if (sz * 4 > drm_buffer_unprocessed(cmdbuf->buffer))
                return -EINVAL;

	BEGIN_RING(5 + sz);
	OUT_RING_REG(RADEON_SE_TCL_STATE_FLUSH, 0);
	OUT_RING(CP_PACKET0(RADEON_SE_TCL_VECTOR_INDX_REG, 0));
	OUT_RING(start | (1 << RADEON_VEC_INDX_OCTWORD_STRIDE_SHIFT));
	OUT_RING(CP_PACKET0_TABLE(RADEON_SE_TCL_VECTOR_DATA_REG, (sz - 1)));
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, sz);
	ADVANCE_RING();

	return 0;
}