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
typedef  int u32 ;
struct via_cputemp_data {int /*<<< orphan*/  msr; int /*<<< orphan*/  id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 struct via_cputemp_data* dev_get_drvdata (struct device*) ; 
 int rdmsr_safe_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_temp(struct device *dev,
			 struct device_attribute *devattr, char *buf)
{
	struct via_cputemp_data *data = dev_get_drvdata(dev);
	u32 eax, edx;
	int err;

	err = rdmsr_safe_on_cpu(data->id, data->msr, &eax, &edx);
	if (err)
		return -EAGAIN;

	err = sprintf(buf, "%d\n", (eax & 0xffffff) * 1000);

	return err;
}