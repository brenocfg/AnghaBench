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
struct dm_cell_key {scalar_t__ virtual; scalar_t__ dev; scalar_t__ block; } ;

/* Variables and functions */

__attribute__((used)) static int keys_equal(struct dm_cell_key *lhs, struct dm_cell_key *rhs)
{
	       return (lhs->virtual == rhs->virtual) &&
		       (lhs->dev == rhs->dev) &&
		       (lhs->block == rhs->block);
}