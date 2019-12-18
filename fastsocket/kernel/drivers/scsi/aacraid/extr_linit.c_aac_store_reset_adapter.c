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
struct aac_dev {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int aac_reset_adapter (struct aac_dev*,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* class_to_shost (struct device*) ; 

__attribute__((used)) static ssize_t aac_store_reset_adapter(struct device *device,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	int retval = -EACCES;

	if (!capable(CAP_SYS_ADMIN))
		return retval;
	retval = aac_reset_adapter((struct aac_dev*)class_to_shost(device)->hostdata, buf[0] == '!');
	if (retval >= 0)
		retval = count;
	return retval;
}