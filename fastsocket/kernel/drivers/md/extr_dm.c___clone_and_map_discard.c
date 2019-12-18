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
struct dm_target {int /*<<< orphan*/  num_discard_requests; int /*<<< orphan*/  split_discard_requests; } ;
struct clone_info {int /*<<< orphan*/  sector; int /*<<< orphan*/  sector_count; int /*<<< orphan*/  map; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  __issue_target_requests (struct clone_info*,struct dm_target*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct dm_target* dm_table_find_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_target_is_valid (struct dm_target*) ; 
 int /*<<< orphan*/  max_io_len (int /*<<< orphan*/ ,struct dm_target*) ; 
 int /*<<< orphan*/  max_io_len_target_boundary (int /*<<< orphan*/ ,struct dm_target*) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __clone_and_map_discard(struct clone_info *ci)
{
	struct dm_target *ti;
	sector_t len;

	do {
		ti = dm_table_find_target(ci->map, ci->sector);
		if (!dm_target_is_valid(ti))
			return -EIO;

		/*
		 * Even though the device advertised discard support,
		 * that does not mean every target supports it, and
		 * reconfiguration might also have changed that since the
		 * check was performed.
		 */
		if (!ti->num_discard_requests)
			return -EOPNOTSUPP;

		if (!ti->split_discard_requests)
			len = min(ci->sector_count, max_io_len_target_boundary(ci->sector, ti));
		else
			len = min(ci->sector_count, max_io_len(ci->sector, ti));

		__issue_target_requests(ci, ti, ti->num_discard_requests, len);

		ci->sector += len;
	} while (ci->sector_count -= len);

	return 0;
}