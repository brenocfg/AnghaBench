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
typedef  union map_info {int dummy; } map_info ;
struct dm_target_io {union map_info info; } ;
struct bio {scalar_t__ bi_private; } ;

/* Variables and functions */

union map_info *dm_get_mapinfo(struct bio *bio)
{
	if (bio && bio->bi_private)
		return &((struct dm_target_io *)bio->bi_private)->info;
	return NULL;
}