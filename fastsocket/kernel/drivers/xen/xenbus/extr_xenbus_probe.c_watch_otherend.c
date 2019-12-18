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
struct xenbus_device {int /*<<< orphan*/  otherend; int /*<<< orphan*/  otherend_watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  otherend_changed ; 
 int xenbus_watch_pathfmt (struct xenbus_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int watch_otherend(struct xenbus_device *dev)
{
	return xenbus_watch_pathfmt(dev, &dev->otherend_watch, otherend_changed,
				    "%s/%s", dev->otherend, "state");
}