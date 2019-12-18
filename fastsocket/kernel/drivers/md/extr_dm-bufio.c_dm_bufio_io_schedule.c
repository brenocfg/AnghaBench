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
struct dm_bufio_client {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_unplug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_schedule () ; 

__attribute__((used)) static void dm_bufio_io_schedule(struct dm_bufio_client *c)
{
	blk_unplug(bdev_get_queue(c->bdev));
	io_schedule();
}