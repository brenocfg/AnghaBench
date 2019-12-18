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
struct dm_target {int /*<<< orphan*/  len; struct dm_dev* private; } ;
struct dm_dev {int dummy; } ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,struct dm_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static int origin_iterate_devices(struct dm_target *ti,
				  iterate_devices_callout_fn fn, void *data)
{
	struct dm_dev *dev = ti->private;

	return fn(ti, dev, 0, ti->len, data);
}