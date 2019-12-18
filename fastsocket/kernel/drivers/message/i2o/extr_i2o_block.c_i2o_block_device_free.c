#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2o_block_device {TYPE_1__* gd; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i2o_block_device*) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 

__attribute__((used)) static void i2o_block_device_free(struct i2o_block_device *dev)
{
	blk_cleanup_queue(dev->gd->queue);

	put_disk(dev->gd);

	kfree(dev);
}