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
struct dm_target {int /*<<< orphan*/  num_flush_requests; } ;
struct clone_info {int /*<<< orphan*/  map; int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __issue_target_requests (struct clone_info*,struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_has_data (int /*<<< orphan*/ ) ; 
 struct dm_target* dm_table_get_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __clone_and_map_empty_flush(struct clone_info *ci)
{
	unsigned target_nr = 0;
	struct dm_target *ti;

	BUG_ON(bio_has_data(ci->bio));
	while ((ti = dm_table_get_target(ci->map, target_nr++)))
		__issue_target_requests(ci, ti, ti->num_flush_requests, 0);

	return 0;
}