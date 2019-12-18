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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int applesmc_get_key_at_index (int /*<<< orphan*/ ,char*) ; 
 int applesmc_get_key_type (char*,char*) ; 
 int /*<<< orphan*/  applesmc_lock ; 
 int /*<<< orphan*/  key_at_index ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char) ; 

__attribute__((used)) static ssize_t applesmc_key_at_index_data_length_show(struct device *dev,
				struct device_attribute *attr, char *sysfsbuf)
{
	char key[5];
	char info[6];
	int ret;

	mutex_lock(&applesmc_lock);

	ret = applesmc_get_key_at_index(key_at_index, key);

	if (ret || !key[0]) {
		mutex_unlock(&applesmc_lock);

		return -EINVAL;
	}

	ret = applesmc_get_key_type(key, info);

	mutex_unlock(&applesmc_lock);

	if (!ret)
		return snprintf(sysfsbuf, PAGE_SIZE, "%d\n", info[0]);
	else
		return ret;
}