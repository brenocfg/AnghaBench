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
struct dm_target {struct delay_c* private; } ;
struct delay_c {int /*<<< orphan*/  delayed_pool; scalar_t__ dev_write; scalar_t__ dev_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdelayd_wq ; 
 int /*<<< orphan*/  kfree (struct delay_c*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delay_dtr(struct dm_target *ti)
{
	struct delay_c *dc = ti->private;

	flush_workqueue(kdelayd_wq);

	dm_put_device(ti, dc->dev_read);

	if (dc->dev_write)
		dm_put_device(ti, dc->dev_write);

	mempool_destroy(dc->delayed_pool);
	kfree(dc);
}