#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct queue_limits {int max_discard_sectors; int discard_granularity; } ;
struct TYPE_4__ {scalar_t__ discard_passdown; } ;
struct pool_c {TYPE_2__* data_dev; TYPE_1__ adjusted_pf; struct pool* pool; } ;
struct pool {int sectors_per_block; } ;
struct TYPE_6__ {struct queue_limits limits; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 TYPE_3__* bdev_get_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_discard_limits(struct pool_c *pt, struct queue_limits *limits)
{
	struct pool *pool = pt->pool;
	struct queue_limits *data_limits;

	limits->max_discard_sectors = pool->sectors_per_block;

	/*
	 * discard_granularity is just a hint, and not enforced.
	 */
	if (pt->adjusted_pf.discard_passdown) {
		data_limits = &bdev_get_queue(pt->data_dev->bdev)->limits;
		limits->discard_granularity = data_limits->discard_granularity;
	} else
		limits->discard_granularity = pool->sectors_per_block << SECTOR_SHIFT;
}