#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_2__* s_bdev; int /*<<< orphan*/ * s_bdi; int /*<<< orphan*/  s_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 TYPE_1__* bdev_get_queue (TYPE_2__*) ; 

__attribute__((used)) static int set_gfs2_super(struct super_block *s, void *data)
{
	s->s_bdev = data;
	s->s_dev = s->s_bdev->bd_dev;

	/*
	 * We set the bdi here to the queue backing, file systems can
	 * overwrite this in ->fill_super()
	 */
	s->s_bdi = &bdev_get_queue(s->s_bdev)->backing_dev_info;
	return 0;
}