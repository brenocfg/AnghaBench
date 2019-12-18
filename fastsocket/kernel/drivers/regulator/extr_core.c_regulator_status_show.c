#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_2__* desc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_status ) (struct regulator_dev*) ;} ;

/* Variables and functions */
 int ERANGE ; 
#define  REGULATOR_STATUS_ERROR 134 
#define  REGULATOR_STATUS_FAST 133 
#define  REGULATOR_STATUS_IDLE 132 
#define  REGULATOR_STATUS_NORMAL 131 
#define  REGULATOR_STATUS_OFF 130 
#define  REGULATOR_STATUS_ON 129 
#define  REGULATOR_STATUS_STANDBY 128 
 struct regulator_dev* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,char*) ; 
 int stub1 (struct regulator_dev*) ; 

__attribute__((used)) static ssize_t regulator_status_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);
	int status;
	char *label;

	status = rdev->desc->ops->get_status(rdev);
	if (status < 0)
		return status;

	switch (status) {
	case REGULATOR_STATUS_OFF:
		label = "off";
		break;
	case REGULATOR_STATUS_ON:
		label = "on";
		break;
	case REGULATOR_STATUS_ERROR:
		label = "error";
		break;
	case REGULATOR_STATUS_FAST:
		label = "fast";
		break;
	case REGULATOR_STATUS_NORMAL:
		label = "normal";
		break;
	case REGULATOR_STATUS_IDLE:
		label = "idle";
		break;
	case REGULATOR_STATUS_STANDBY:
		label = "standby";
		break;
	default:
		return -ERANGE;
	}

	return sprintf(buf, "%s\n", label);
}