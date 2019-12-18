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
struct atm_dev {int link_rate; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  ATM_25_PCR 130 
#define  ATM_OC12_PCR 129 
#define  ATM_OC3_PCR 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct atm_dev* to_atm_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_link_rate(struct device *cdev,
			      struct device_attribute *attr, char *buf)
{
	char *pos = buf;
	struct atm_dev *adev = to_atm_dev(cdev);
	int link_rate;

	/* show the link rate, not the data rate */
	switch (adev->link_rate) {
		case ATM_OC3_PCR:
			link_rate = 155520000;
			break;
		case ATM_OC12_PCR:
			link_rate = 622080000;
			break;
		case ATM_25_PCR:
			link_rate = 25600000;
			break;
		default:
			link_rate = adev->link_rate * 8 * 53;
	}
	pos += sprintf(pos, "%d\n", link_rate);

	return pos - buf;
}