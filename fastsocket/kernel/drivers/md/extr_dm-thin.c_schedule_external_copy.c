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
struct thin_c {int /*<<< orphan*/  origin_dev; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_copy (struct thin_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_bio_prison_cell*,struct bio*) ; 

__attribute__((used)) static void schedule_external_copy(struct thin_c *tc, dm_block_t virt_block,
				   dm_block_t data_dest,
				   struct dm_bio_prison_cell *cell, struct bio *bio)
{
	schedule_copy(tc, virt_block, tc->origin_dev,
		      virt_block, data_dest, cell, bio);
}