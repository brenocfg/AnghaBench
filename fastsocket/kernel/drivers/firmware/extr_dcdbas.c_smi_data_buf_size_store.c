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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 size_t smi_data_buf_realloc (unsigned long) ; 
 int /*<<< orphan*/  smi_data_lock ; 

__attribute__((used)) static ssize_t smi_data_buf_size_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	unsigned long buf_size;
	ssize_t ret;

	buf_size = simple_strtoul(buf, NULL, 10);

	/* make sure SMI data buffer is at least buf_size */
	mutex_lock(&smi_data_lock);
	ret = smi_data_buf_realloc(buf_size);
	mutex_unlock(&smi_data_lock);
	if (ret)
		return ret;

	return count;
}