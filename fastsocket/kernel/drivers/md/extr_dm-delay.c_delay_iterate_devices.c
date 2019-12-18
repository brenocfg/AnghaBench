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
struct dm_target {int /*<<< orphan*/  len; struct delay_c* private; } ;
struct delay_c {int /*<<< orphan*/  start_write; scalar_t__ dev_write; int /*<<< orphan*/  start_read; scalar_t__ dev_read; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static int delay_iterate_devices(struct dm_target *ti,
				 iterate_devices_callout_fn fn, void *data)
{
	struct delay_c *dc = ti->private;
	int ret = 0;

	ret = fn(ti, dc->dev_read, dc->start_read, ti->len, data);
	if (ret)
		goto out;

	if (dc->dev_write)
		ret = fn(ti, dc->dev_write, dc->start_write, ti->len, data);

out:
	return ret;
}