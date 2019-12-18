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
struct lm92_data {int /*<<< orphan*/  temp1_hyst; int /*<<< orphan*/  temp1_crit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int TEMP_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm92_data* lm92_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_temp1_crit_hyst(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct lm92_data *data = lm92_update_device(dev);
	return sprintf(buf, "%d\n", TEMP_FROM_REG(data->temp1_crit)
		       - TEMP_FROM_REG(data->temp1_hyst));
}