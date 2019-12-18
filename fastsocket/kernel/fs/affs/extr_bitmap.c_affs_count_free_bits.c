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
typedef  int u32 ;

/* Variables and functions */
 int* nibblemap ; 

__attribute__((used)) static u32
affs_count_free_bits(u32 blocksize, const void *data)
{
	const u32 *map;
	u32 free;
	u32 tmp;

	map = data;
	free = 0;
	for (blocksize /= 4; blocksize > 0; blocksize--) {
		tmp = *map++;
		while (tmp) {
			free += nibblemap[tmp & 0xf];
			tmp >>= 4;
		}
	}

	return free;
}