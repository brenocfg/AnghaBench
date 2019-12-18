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
struct dm_target {struct dm_dev* private; } ;
struct dm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_device (struct dm_target*,struct dm_dev*) ; 

__attribute__((used)) static void origin_dtr(struct dm_target *ti)
{
	struct dm_dev *dev = ti->private;
	dm_put_device(ti, dev);
}