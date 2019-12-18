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
struct sysdev_attribute {int dummy; } ;
struct sys_device {int id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int reload_for_cpu (int) ; 
 unsigned long simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t reload_store(struct sys_device *dev,
			    struct sysdev_attribute *attr,
			    const char *buf, size_t size)
{
	unsigned long val;
	int cpu = dev->id;
	int ret = 0;
	char *end;

	val = simple_strtoul(buf, &end, 0);
	if (end == buf)
		return -EINVAL;

	if (val == 1) {
		get_online_cpus();
		if (cpu_online(cpu))
			ret = reload_for_cpu(cpu);
		put_online_cpus();
	}

	if (!ret)
		ret = size;

	return ret;
}