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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dasd_uid {scalar_t__ type; } ;
struct dasd_device {TYPE_1__* discipline; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_uid ) (struct dasd_device*,struct dasd_uid*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 scalar_t__ UA_BASE_PAV_ALIAS ; 
 scalar_t__ UA_HYPER_PAV_ALIAS ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*,struct dasd_uid*) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t dasd_alias_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct dasd_device *device;
	struct dasd_uid uid;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		return sprintf(buf, "0\n");

	if (device->discipline && device->discipline->get_uid &&
	    !device->discipline->get_uid(device, &uid)) {
		if (uid.type == UA_BASE_PAV_ALIAS ||
		    uid.type == UA_HYPER_PAV_ALIAS) {
			dasd_put_device(device);
			return sprintf(buf, "1\n");
		}
	}
	dasd_put_device(device);

	return sprintf(buf, "0\n");
}