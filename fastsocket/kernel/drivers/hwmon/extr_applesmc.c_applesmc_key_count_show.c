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
typedef  int u8 ;
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_COUNT_KEY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  applesmc_lock ; 
 int applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t applesmc_key_count_show(struct device *dev,
				struct device_attribute *attr, char *sysfsbuf)
{
	int ret;
	u8 buffer[4];
	u32 count;

	mutex_lock(&applesmc_lock);

	ret = applesmc_read_key(KEY_COUNT_KEY, buffer, 4);
	count = ((u32)buffer[0]<<24) + ((u32)buffer[1]<<16) +
						((u32)buffer[2]<<8) + buffer[3];

	mutex_unlock(&applesmc_lock);
	if (ret)
		return ret;
	else
		return snprintf(sysfsbuf, PAGE_SIZE, "%d\n", count);
}