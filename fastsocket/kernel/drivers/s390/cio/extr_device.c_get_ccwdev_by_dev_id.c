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
struct device {int dummy; } ;
struct ccw_device {int dummy; } ;
struct ccw_dev_id {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ccw_dev_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_bus_type ; 
 int /*<<< orphan*/  match_dev_id ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static struct ccw_device *get_ccwdev_by_dev_id(struct ccw_dev_id *dev_id)
{
	struct device *dev;

	dev = bus_find_device(&ccw_bus_type, NULL, dev_id, match_dev_id);

	return dev ? to_ccwdev(dev) : NULL;
}