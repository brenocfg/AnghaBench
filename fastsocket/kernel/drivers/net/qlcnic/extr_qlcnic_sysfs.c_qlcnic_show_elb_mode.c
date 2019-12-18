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
struct qlcnic_adapter {int /*<<< orphan*/  state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __QLCNIC_ELB_INPROGRESS ; 
 struct qlcnic_adapter* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t qlcnic_show_elb_mode(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct qlcnic_adapter *adapter = dev_get_drvdata(dev);

	if (test_bit(__QLCNIC_ELB_INPROGRESS, &adapter->state))
		return sprintf(buf,  "1\n");

	return sprintf(buf, "0\n");
}