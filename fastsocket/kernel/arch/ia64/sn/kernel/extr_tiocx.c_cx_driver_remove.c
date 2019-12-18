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
struct cx_drv {int /*<<< orphan*/  (* remove ) (struct cx_dev*) ;} ;
struct cx_dev {struct cx_drv* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cx_dev*) ; 
 struct cx_dev* to_cx_dev (struct device*) ; 

__attribute__((used)) static int cx_driver_remove(struct device *dev)
{
	struct cx_dev *cx_dev = to_cx_dev(dev);
	struct cx_drv *cx_drv = cx_dev->driver;
	if (cx_drv->remove)
		cx_drv->remove(cx_dev);
	cx_dev->driver = NULL;
	return 0;
}