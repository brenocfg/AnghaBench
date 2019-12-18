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
struct atm_dev {int* esi; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ESI_LEN ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct atm_dev* to_atm_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_address(struct device *cdev,
			    struct device_attribute *attr, char *buf)
{
	char *pos = buf;
	struct atm_dev *adev = to_atm_dev(cdev);
	int i;

	for (i = 0; i < (ESI_LEN - 1); i++)
		pos += sprintf(pos, "%02x:", adev->esi[i]);
	pos += sprintf(pos, "%02x\n", adev->esi[i]);

	return pos - buf;
}