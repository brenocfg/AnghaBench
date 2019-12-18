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
typedef  int u32 ;
struct TYPE_2__ {int md_capture_mask; } ;
struct netxen_adapter {TYPE_1__ mdump; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct netxen_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
netxen_show_fwdump_level(struct device *dev,
			  struct device_attribute *attr, char *buf)
{
	struct netxen_adapter *adapter = dev_get_drvdata(dev);
	u32 size = adapter->mdump.md_capture_mask;
	return sprintf(buf, "%u\n", size);
}