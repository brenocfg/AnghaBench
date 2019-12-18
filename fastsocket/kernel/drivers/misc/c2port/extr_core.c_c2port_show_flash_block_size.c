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
struct c2port_ops {int block_size; } ;
struct c2port_device {struct c2port_ops* ops; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct c2port_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t c2port_show_flash_block_size(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct c2port_device *c2dev = dev_get_drvdata(dev);
	struct c2port_ops *ops = c2dev->ops;

	return sprintf(buf, "%d\n", ops->block_size);
}