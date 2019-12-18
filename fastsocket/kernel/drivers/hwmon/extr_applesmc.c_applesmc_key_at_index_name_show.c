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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int applesmc_get_key_at_index (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  applesmc_lock ; 
 int /*<<< orphan*/  key_at_index ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t applesmc_key_at_index_name_show(struct device *dev,
				struct device_attribute *attr, char *sysfsbuf)
{
	char key[5];
	int ret;

	mutex_lock(&applesmc_lock);

	ret = applesmc_get_key_at_index(key_at_index, key);

	mutex_unlock(&applesmc_lock);

	if (!ret && key[0])
		return snprintf(sysfsbuf, PAGE_SIZE, "%s\n", key);
	else
		return -EINVAL;
}