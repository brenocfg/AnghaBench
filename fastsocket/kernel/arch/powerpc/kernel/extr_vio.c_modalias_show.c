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
struct vio_dev {char* type; } ;
struct device_node {int dummy; } ;
struct device_attribute {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	const struct vio_dev *vio_dev = to_vio_dev(dev);
	struct device_node *dn;
	const char *cp;

	dn = dev->archdata.of_node;
	if (!dn)
		return -ENODEV;
	cp = of_get_property(dn, "compatible", NULL);
	if (!cp)
		return -ENODEV;

	return sprintf(buf, "vio:T%sS%s\n", vio_dev->type, cp);
}