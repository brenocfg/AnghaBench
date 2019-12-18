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
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct blkfront_info {int dummy; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
#define  XenbusStateClosed 134 
#define  XenbusStateClosing 133 
#define  XenbusStateConnected 132 
#define  XenbusStateInitWait 131 
#define  XenbusStateInitialised 130 
#define  XenbusStateInitialising 129 
#define  XenbusStateUnknown 128 
 int /*<<< orphan*/  blkfront_closing (struct blkfront_info*) ; 
 int /*<<< orphan*/  blkfront_connect (struct blkfront_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct blkfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blkback_changed(struct xenbus_device *dev,
			    enum xenbus_state backend_state)
{
	struct blkfront_info *info = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "blkfront:blkback_changed to state %d.\n", backend_state);

	switch (backend_state) {
	case XenbusStateInitialising:
	case XenbusStateInitWait:
	case XenbusStateInitialised:
	case XenbusStateUnknown:
	case XenbusStateClosed:
		break;

	case XenbusStateConnected:
		blkfront_connect(info);
		break;

	case XenbusStateClosing:
		blkfront_closing(info);
		break;
	}
}