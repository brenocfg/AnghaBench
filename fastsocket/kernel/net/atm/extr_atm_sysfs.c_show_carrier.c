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
struct atm_dev {scalar_t__ signal; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ATM_PHY_SIG_LOST ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct atm_dev* to_atm_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_carrier(struct device *cdev,
			    struct device_attribute *attr, char *buf)
{
	char *pos = buf;
	struct atm_dev *adev = to_atm_dev(cdev);

	pos += sprintf(pos, "%d\n",
		       adev->signal == ATM_PHY_SIG_LOST ? 0 : 1);

	return pos - buf;
}