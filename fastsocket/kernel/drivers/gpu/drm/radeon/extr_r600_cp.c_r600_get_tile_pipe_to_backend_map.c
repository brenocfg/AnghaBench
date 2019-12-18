#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u32 ;

/* Variables and functions */
 int R6XX_MAX_BACKENDS ; 
 int R6XX_MAX_PIPES ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 r600_get_tile_pipe_to_backend_map(u32 num_tile_pipes,
					     u32 num_backends,
					     u32 backend_disable_mask)
{
	u32 backend_map = 0;
	u32 enabled_backends_mask;
	u32 enabled_backends_count;
	u32 cur_pipe;
	u32 swizzle_pipe[R6XX_MAX_PIPES];
	u32 cur_backend;
	u32 i;

	if (num_tile_pipes > R6XX_MAX_PIPES)
		num_tile_pipes = R6XX_MAX_PIPES;
	if (num_tile_pipes < 1)
		num_tile_pipes = 1;
	if (num_backends > R6XX_MAX_BACKENDS)
		num_backends = R6XX_MAX_BACKENDS;
	if (num_backends < 1)
		num_backends = 1;

	enabled_backends_mask = 0;
	enabled_backends_count = 0;
	for (i = 0; i < R6XX_MAX_BACKENDS; ++i) {
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

	memset((uint8_t *)&swizzle_pipe[0], 0, sizeof(u32) * R6XX_MAX_PIPES);
	switch (num_tile_pipes) {
	case 1:
		swizzle_pipe[0] = 0;
		break;
	case 2:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 1;
		break;
	case 3:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 1;
		swizzle_pipe[2] = 2;
		break;
	case 4:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 1;
		swizzle_pipe[2] = 2;
		swizzle_pipe[3] = 3;
		break;
	case 5:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 1;
		swizzle_pipe[2] = 2;
		swizzle_pipe[3] = 3;
		swizzle_pipe[4] = 4;
		break;
	case 6:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 2;
		swizzle_pipe[2] = 4;
		swizzle_pipe[3] = 5;
		swizzle_pipe[4] = 1;
		swizzle_pipe[5] = 3;
		break;
	case 7:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 2;
		swizzle_pipe[2] = 4;
		swizzle_pipe[3] = 6;
		swizzle_pipe[4] = 1;
		swizzle_pipe[5] = 3;
		swizzle_pipe[6] = 5;
		break;
	case 8:
		swizzle_pipe[0] = 0;
		swizzle_pipe[1] = 2;
		swizzle_pipe[2] = 4;
		swizzle_pipe[3] = 6;
		swizzle_pipe[4] = 1;
		swizzle_pipe[5] = 3;
		swizzle_pipe[6] = 5;
		swizzle_pipe[7] = 7;
		break;
	}

	cur_backend = 0;
	for (cur_pipe = 0; cur_pipe < num_tile_pipes; ++cur_pipe) {
		while (((1 << cur_backend) & enabled_backends_mask) == 0)
			cur_backend = (cur_backend + 1) % R6XX_MAX_BACKENDS;

		backend_map |= (u32)(((cur_backend & 3) << (swizzle_pipe[cur_pipe] * 2)));

		cur_backend = (cur_backend + 1) % R6XX_MAX_BACKENDS;
	}

	return backend_map;
}