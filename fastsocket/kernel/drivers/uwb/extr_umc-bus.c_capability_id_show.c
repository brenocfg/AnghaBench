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
struct umc_dev {int cap_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct umc_dev* to_umc_dev (struct device*) ; 

__attribute__((used)) static ssize_t capability_id_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct umc_dev *umc = to_umc_dev(dev);

	return sprintf(buf, "0x%02x\n", umc->cap_id);
}