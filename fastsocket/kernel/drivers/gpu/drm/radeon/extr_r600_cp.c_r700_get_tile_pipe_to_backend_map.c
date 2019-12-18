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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u32 ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
#define  CHIP_RV710 131 
#define  CHIP_RV730 130 
#define  CHIP_RV740 129 
#define  CHIP_RV770 128 
 int R7XX_MAX_BACKENDS ; 
 int R7XX_MAX_PIPES ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 r700_get_tile_pipe_to_backend_map(drm_radeon_private_t *dev_priv,
					     u32 num_tile_pipes,
					     u32 num_backends,
					     u32 backend_disable_mask)
{
	u32 backend_map = 0;
	u32 enabled_backends_mask;
	u32 enabled_backends_count;
	u32 cur_pipe;
	u32 swizzle_pipe[R7XX_MAX_PIPES];
	u32 cur_backend;
	u32 i;
	bool force_no_swizzle;

	if (num_tile_pipes > R7XX_MAX_PIPES)
		num_tile_pipes = R7XX_MAX_PIPES;
	if (num_tile_pipes < 1)
		num_tile_pipes = 1;
	if (num_backends > R7XX_MAX_BACKENDS)
		num_backends = R7XX_MAX_BACKENDS;
	if (num_backends < 1)
		num_backends = 1;

	enabled_backends_mask = 0;
	enabled_backends_count = 0;
	for (i = 0; i < R7XX_MAX_BACKENDS; ++i) {
		if (((backend_disable_mask >> i) & 1) == 0) {
			enabled_backends_mask |= (1 << i);
			++enabled_backends_count;
		}
		if (enabled_backends_count == num_backends)
			break;
	}

	if (enabled_backends_count == 0) {
		enabled_backends_mask = 1;
		enabled_backends_count = 1;
	}

	if (enabled_backends_count != num_backends)
		num_backends = enabled_backends_count;

	switch (dev_priv->flags & RADEON_FAMILY_MASK) {
	case CHIP_RV770:
	case CHIP_RV730:
		force_no_swizzle = false;
		break;
	case CHIP_RV710:
	case CHIP_RV740:
	default:
		force_no_swizzle = true;
		break;
	}

	memset((uint8_t *)&swizzle_pipe[0], 0, sizeof(u32) * R7XX_MAX_PIPES);
	switch (num_tile_pipes) {
	case 1:
		swizzle_pipe[0] = 0;
		break;
	case 2:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 1;
		break;
	case 3:
		if (force_no_swizzle) {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 1;
			swizzle_pipe[2] = 2;
		} else {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 2;
			swizzle_pipe[2] = 1;
		}
		break;
	case 4:
		if (force_no_swizzle) {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 1;
			swizzle_pipe[2] = 2;
			swizzle_pipe[3] = 3;
		} else {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 2;
			swizzle_pipe[2] = 3;
			swizzle_pipe[3] = 1;
		}
		break;
	case 5:
		if (force_no_swizzle) {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 1;
			swizzle_pipe[2] = 2;
			swizzle_pipe[3] = 3;
			swizzle_pipe[4] = 4;
		} else {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 2;
			swizzle_pipe[2] = 4;
			swizzle_pipe[3] = 1;
			swizzle_pipe[4] = 3;
		}
		break;
	case 6:
		if (force_no_swizzle) {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 1;
			swizzle_pipe[2] = 2;
			swizzle_pipe[3] = 3;
			swizzle_pipe[4] = 4;
			swizzle_pipe[5] = 5;
		} else {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 2;
			swizzle_pipe[2] = 4;
			swizzle_pipe[3] = 5;
			swizzle_pipe[4] = 3;
			swizzle_pipe[5] = 1;
		}
		break;
	case 7:
		if (force_no_swizzle) {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 1;
			swizzle_pipe[2] = 2;
			swizzle_pipe[3] = 3;
			swizzle_pipe[4] = 4;
			swizzle_pipe[5] = 5;
			swizzle_pipe[6] = 6;
		} else {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 2;
			swizzle_pipe[2] = 4;
			swizzle_pipe[3] = 6;
			swizzle_pipe[4] = 3;
			swizzle_pipe[5] = 1;
			swizzle_pipe[6] = 5;
		}
		break;
	case 8:
		if (force_no_swizzle) {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 1;
			swizzle_pipe[2] = 2;
			swizzle_pipe[3] = 3;
			swizzle_pipe[4] = 4;
			swizzle_pipe[5] = 5;
			swizzle_pipe[6] = 6;
			swizzle_pipe[7] = 7;
		} else {
			swizzle_pipe[0] = 0;
			swizzle_pipe[1] = 2;
			swizzle_pipe[2] = 4;
			swizzle_pipe[3] = 6;
			swizzle_pipe[4] = 3;
			swizzle_pipe[5] = 1;
			swizzle_pipe[6] = 7;
			swizzle_pipe[7] = 5;
		}
		break;
	}

	cur_backend = 0;
	for (cur_pipe = 0; cur_pipe < num_tile_pipes; ++cur_pipe) {
		while (((1 << cur_backend) & enabled_backends_mask) == 0)
			cur_backend = (cur_backend + 1) % R7XX_MAX_BACKENDS;

		backend_map |= (u32)(((cur_backend & 3) << (swizzle_pipe[cur_pipe] * 2)));

		cur_backend = (cur_backend + 1) % R7XX_MAX_BACKENDS;
	}

	return backend_map;
}