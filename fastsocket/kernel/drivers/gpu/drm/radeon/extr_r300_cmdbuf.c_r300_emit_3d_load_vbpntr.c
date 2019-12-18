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
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 int EINVAL ; 
 int MAX_ARRAY_PACKET ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  OUT_RING_DRM_BUFFER (int /*<<< orphan*/ ,int) ; 
 int RADEON_CP_PACKET_COUNT_MASK ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/  drm_buffer_advance (int /*<<< orphan*/ ,int) ; 
 int* drm_buffer_pointer_to_dword (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_check_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline__ int r300_emit_3d_load_vbpntr(drm_radeon_private_t *dev_priv,
					       drm_radeon_kcmd_buffer_t *cmdbuf,
					       u32 header)
{
	int count, i, k;
#define MAX_ARRAY_PACKET  64
	u32 *data;
	u32 narrays;
	RING_LOCALS;

	count = (header & RADEON_CP_PACKET_COUNT_MASK) >> 16;

	if ((count + 1) > MAX_ARRAY_PACKET) {
		DRM_ERROR("Too large payload in 3D_LOAD_VBPNTR (count=%d)\n",
			  count);
		return -EINVAL;
	}
	/* carefully check packet contents */

	/* We have already read the header so advance the buffer. */
	drm_buffer_advance(cmdbuf->buffer, 4);

	narrays = *(u32 *)drm_buffer_pointer_to_dword(cmdbuf->buffer, 0);
	k = 0;
	i = 1;
	while ((k < narrays) && (i < (count + 1))) {
		i++;		/* skip attribute field */
		data = drm_buffer_pointer_to_dword(cmdbuf->buffer, i);
		if (!radeon_check_offset(dev_priv, *data)) {
			DRM_ERROR
			    ("Offset failed range check (k=%d i=%d) while processing 3D_LOAD_VBPNTR packet.\n",
			     k, i);
			return -EINVAL;
		}
		k++;
		i++;
		if (k == narrays)
			break;
		/* have one more to process, they come in pairs */
		data = drm_buffer_pointer_to_dword(cmdbuf->buffer, i);
		if (!radeon_check_offset(dev_priv, *data)) {
			DRM_ERROR
			    ("Offset failed range check (k=%d i=%d) while processing 3D_LOAD_VBPNTR packet.\n",
			     k, i);
			return -EINVAL;
		}
		k++;
		i++;
	}
	/* do the counts match what we expect ? */
	if ((k != narrays) || (i != (count + 1))) {
		DRM_ERROR
		    ("Malformed 3D_LOAD_VBPNTR packet (k=%d i=%d narrays=%d count+1=%d).\n",
		     k, i, narrays, count + 1);
		return -EINVAL;
	}

	/* all clear, output packet */

	BEGIN_RING(count + 2);
	OUT_RING(header);
	OUT_RING_DRM_BUFFER(cmdbuf->buffer, count + 1);
	ADVANCE_RING();

	return 0;
}