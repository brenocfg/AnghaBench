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
typedef  int /*<<< orphan*/  u16 ;
struct i2o_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_parm_field_get (struct i2o_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static ssize_t i2o_exec_show_vendor_id(struct device *d,
				       struct device_attribute *attr, char *buf)
{
	struct i2o_device *dev = to_i2o_device(d);
	u16 id;

	if (!i2o_parm_field_get(dev, 0x0000, 0, &id, 2)) {
		sprintf(buf, "0x%04x", le16_to_cpu(id));
		return strlen(buf) + 1;
	}

	return 0;
}