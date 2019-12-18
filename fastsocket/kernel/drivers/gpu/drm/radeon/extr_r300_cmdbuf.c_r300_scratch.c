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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  stack_ptr_addr ;
struct TYPE_9__ {scalar_t__* scratch_ages; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ drm_radeon_kcmd_buffer_t ;
struct TYPE_8__ {int n_bufs; int reg; } ;
struct TYPE_11__ {TYPE_1__ scratch; } ;
typedef  TYPE_4__ drm_r300_cmd_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 scalar_t__ CP_PACKET0 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_COPY_FROM_USER (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ DRM_COPY_TO_USER (scalar_t__*,scalar_t__*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (scalar_t__) ; 
 scalar_t__ RADEON_SCRATCH_REG0 ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  drm_buffer_advance (int /*<<< orphan*/ ,int) ; 
 scalar_t__* drm_buffer_pointer_to_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * drm_buffer_read_object (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int drm_buffer_unprocessed (int /*<<< orphan*/ ) ; 
 scalar_t__ get_unaligned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r300_scratch(drm_radeon_private_t *dev_priv,
			drm_radeon_kcmd_buffer_t *cmdbuf,
			drm_r300_cmd_header_t header)
{
	u32 *ref_age_base;
	u32 i, *buf_idx, h_pending;
	u64 *ptr_addr;
	u64 stack_ptr_addr;
	RING_LOCALS;

	if (drm_buffer_unprocessed(cmdbuf->buffer) <
	    (sizeof(u64) + header.scratch.n_bufs * sizeof(*buf_idx))) {
		return -EINVAL;
	}

	if (header.scratch.reg >= 5) {
		return -EINVAL;
	}

	dev_priv->scratch_ages[header.scratch.reg]++;

	ptr_addr = drm_buffer_read_object(cmdbuf->buffer,
			sizeof(stack_ptr_addr), &stack_ptr_addr);
	ref_age_base = (u32 *)(unsigned long)get_unaligned(ptr_addr);

	for (i=0; i < header.scratch.n_bufs; i++) {
		buf_idx = drm_buffer_pointer_to_dword(cmdbuf->buffer, 0);
		*buf_idx *= 2; /* 8 bytes per buf */

		if (DRM_COPY_TO_USER(ref_age_base + *buf_idx,
				&dev_priv->scratch_ages[header.scratch.reg],
				sizeof(u32)))
			return -EINVAL;

		if (DRM_COPY_FROM_USER(&h_pending,
				ref_age_base + *buf_idx + 1,
				sizeof(u32)))
			return -EINVAL;

		if (h_pending == 0)
			return -EINVAL;

		h_pending--;

		if (DRM_COPY_TO_USER(ref_age_base + *buf_idx + 1,
					&h_pending,
					sizeof(u32)))
			return -EINVAL;

		drm_buffer_advance(cmdbuf->buffer, sizeof(*buf_idx));
	}

	BEGIN_RING(2);
	OUT_RING( CP_PACKET0( RADEON_SCRATCH_REG0 + header.scratch.reg * 4, 0 ) );
	OUT_RING( dev_priv->scratch_ages[header.scratch.reg] );
	ADVANCE_RING();

	return 0;
}