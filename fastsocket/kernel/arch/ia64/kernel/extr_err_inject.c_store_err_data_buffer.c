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
struct sysdev_attribute {int dummy; } ;
struct sys_device {unsigned int id; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  data3; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int ERR_DATA_BUFFER_SIZE ; 
 TYPE_1__* err_data_buffer ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
store_err_data_buffer(struct sys_device *dev,
			struct sysdev_attribute *attr,
			const char *buf, size_t size)
{
	unsigned int cpu=dev->id;
	int ret;

#ifdef ERR_INJ_DEBUG
	printk("write err_data_buffer=[%lx,%lx,%lx] on cpu%d\n",
		 err_data_buffer[cpu].data1,
		 err_data_buffer[cpu].data2,
		 err_data_buffer[cpu].data3,
		 cpu);
#endif
	ret=sscanf(buf, "%lx, %lx, %lx",
			&err_data_buffer[cpu].data1,
			&err_data_buffer[cpu].data2,
			&err_data_buffer[cpu].data3);
	if (ret!=ERR_DATA_BUFFER_SIZE)
		return -EINVAL;

	return size;
}