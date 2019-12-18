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
struct dm_space_map {int dummy; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int dm_sm_extend (struct dm_space_map*,scalar_t__) ; 
 int dm_sm_get_nr_blocks (struct dm_space_map*,scalar_t__*) ; 

__attribute__((used)) static int __resize_space_map(struct dm_space_map *sm, dm_block_t new_count)
{
	int r;
	dm_block_t old_count;

	r = dm_sm_get_nr_blocks(sm, &old_count);
	if (r)
		return r;

	if (new_count == old_count)
		return 0;

	if (new_count < old_count) {
		DMERR("cannot reduce size of space map");
		return -EINVAL;
	}

	return dm_sm_extend(sm, new_count - old_count);
}