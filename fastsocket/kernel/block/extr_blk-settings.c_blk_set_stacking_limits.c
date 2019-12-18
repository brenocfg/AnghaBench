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
struct queue_limits {int discard_zeroes_data; void* max_sectors; void* max_hw_sectors; int /*<<< orphan*/  max_segments; } ;

/* Variables and functions */
 void* UINT_MAX ; 
 int /*<<< orphan*/  USHORT_MAX ; 
 int /*<<< orphan*/  blk_set_default_limits (struct queue_limits*) ; 

void blk_set_stacking_limits(struct queue_limits *lim)
{
	blk_set_default_limits(lim);

	/* Inherit limits from component devices */
	lim->discard_zeroes_data = 1;
	lim->max_segments = USHORT_MAX;
	lim->max_hw_sectors = UINT_MAX;
	lim->max_sectors = UINT_MAX;
}