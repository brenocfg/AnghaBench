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
struct mrvl_mesh_defaults {int /*<<< orphan*/  channel; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mesh_get_default_parameters (struct device*,struct mrvl_mesh_defaults*) ; 
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static ssize_t channel_get(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct mrvl_mesh_defaults defs;
	int ret;

	ret = mesh_get_default_parameters(dev, &defs);

	if (ret)
		return ret;

	return snprintf(buf, 12, "%d\n", le16_to_cpu(defs.channel));
}