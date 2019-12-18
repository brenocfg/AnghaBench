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
struct TYPE_2__ {int /*<<< orphan*/  device_type; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_sas_device_type_names (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 struct sas_rphy* transport_class_to_rphy (struct device*) ; 

__attribute__((used)) static ssize_t
show_sas_rphy_device_type(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct sas_rphy *rphy = transport_class_to_rphy(dev);

	if (!rphy->identify.device_type)
		return snprintf(buf, 20, "none\n");
	return get_sas_device_type_names(
			rphy->identify.device_type, buf);
}