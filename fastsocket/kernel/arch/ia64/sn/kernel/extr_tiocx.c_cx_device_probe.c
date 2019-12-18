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
struct device {int /*<<< orphan*/  driver; } ;
struct cx_drv {int (* probe ) (struct cx_dev*,struct cx_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct cx_device_id {int dummy; } ;
struct cx_dev {struct cx_drv* driver; } ;

/* Variables and functions */
 struct cx_device_id* cx_device_match (int /*<<< orphan*/ ,struct cx_dev*) ; 
 int stub1 (struct cx_dev*,struct cx_device_id const*) ; 
 struct cx_dev* to_cx_dev (struct device*) ; 
 struct cx_drv* to_cx_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx_device_probe(struct device *dev)
{
	const struct cx_device_id *id;
	struct cx_drv *cx_drv = to_cx_driver(dev->driver);
	struct cx_dev *cx_dev = to_cx_dev(dev);
	int error = 0;

	if (!cx_dev->driver && cx_drv->probe) {
		id = cx_device_match(cx_drv->id_table, cx_dev);
		if (id) {
			if ((error = cx_drv->probe(cx_dev, id)) < 0)
				return error;
			else
				cx_dev->driver = cx_drv;
		}
	}

	return error;
}