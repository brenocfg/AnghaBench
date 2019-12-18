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
struct zcrypt_device {char* type_string; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct zcrypt_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__* to_ap_dev (struct device*) ; 

__attribute__((used)) static ssize_t zcrypt_type_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct zcrypt_device *zdev = to_ap_dev(dev)->private;
	return snprintf(buf, PAGE_SIZE, "%s\n", zdev->type_string);
}