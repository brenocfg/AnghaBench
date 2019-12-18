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
struct txx9_sramc_sysdev {scalar_t__ base; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {size_t size; struct txx9_sramc_sysdev* private; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_toio (scalar_t__,char*,size_t) ; 

__attribute__((used)) static ssize_t txx9_sram_write(struct file *filp, struct kobject *kobj,
			       struct bin_attribute *bin_attr,
			       char *buf, loff_t pos, size_t size)
{
	struct txx9_sramc_sysdev *dev = bin_attr->private;
	size_t ramsize = bin_attr->size;

	if (pos >= ramsize)
		return 0;
	if (pos + size > ramsize)
		size = ramsize - pos;
	memcpy_toio(dev->base + pos, buf, size);
	return size;
}