#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_device {size_t type; int /*<<< orphan*/  id; TYPE_1__* adapter; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dvb_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * dnames ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *dvb_devnode(struct device *dev, mode_t *mode)
{
	struct dvb_device *dvbdev = dev_get_drvdata(dev);

	return kasprintf(GFP_KERNEL, "dvb/adapter%d/%s%d",
		dvbdev->adapter->num, dnames[dvbdev->type], dvbdev->id);
}