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
struct TYPE_6__ {int count; int offset; int stride; } ;
struct TYPE_8__ {TYPE_1__ scalars; } ;
typedef  TYPE_3__ drm_radeon_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int CP_PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CP_PACKET0_TABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int RADEON_SCAL_INDX_DWORD_STRIDE_SHIFT ; 
 int /*<<< orphan*/  RADEON_SE_TCL_SCALAR_DATA_REG ; 
 int /*<<< orphan*/  RADEON_SE_TCL_SCALAR_INDX_REG ; 
 int /*<<< orphan*/  RING_LOCALS ; 

__attribute__((used)) static __inline__ int radeon_emit_scalars(drm_radeon_private_t *dev_priv,
					  drm_radeon_cmd_header_t header,
					  drm_radeon_kcmd_buffer_t *cmdbuf)
{
	int sz = header.scalars.count;
	int start = header.scalars.offset;
	int stride = header.scalars.stride;
	RING_LOCALS;

	BEGIN_RING(3 + sz);
	OUT_RING(CP_PACKET0(RADEON_SE_TCL_SCALAR_INDX_REG, 0));
	OUT_RING(start | (stride << RADEON_SCAL_INDX_DWORD_STRIDE_SHIFT));
	OUT_RING(CP_PACKET0_TABLE(RADEON_SE_TCL_SCALAR_DATA_REG, sz - 1));
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, sz);
	ADVANCE_RING();
	return 0;
}