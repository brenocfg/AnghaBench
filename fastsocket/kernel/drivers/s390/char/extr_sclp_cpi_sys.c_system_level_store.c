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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_cpi_mutex ; 
 unsigned long long simple_strtoull (char const*,char**,int) ; 
 unsigned long long system_level ; 

__attribute__((used)) static ssize_t system_level_store(struct kobject *kobj,
				  struct kobj_attribute *attr,
				  const char *buf,
	size_t len)
{
	unsigned long long level;
	char *endp;

	level = simple_strtoull(buf, &endp, 16);

	if (endp == buf)
		return -EINVAL;
	if (*endp == '\n')
		endp++;
	if (*endp)
		return -EINVAL;

	mutex_lock(&sclp_cpi_mutex);
	system_level = level;
	mutex_unlock(&sclp_cpi_mutex);
	return len;
}