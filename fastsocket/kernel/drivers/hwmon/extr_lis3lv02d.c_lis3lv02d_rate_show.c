#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {scalar_t__ whoami; int /*<<< orphan*/  (* read ) (TYPE_1__*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int CTRL1_DF0 ; 
 int CTRL1_DF1 ; 
 int CTRL1_DR ; 
 int /*<<< orphan*/  CTRL_REG1 ; 
 scalar_t__ LIS_DOUBLE_ID ; 
 int* lis3_12_rates ; 
 int* lis3_8_rates ; 
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t lis3lv02d_rate_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	u8 ctrl;
	int val;

	lis3_dev.read(&lis3_dev, CTRL_REG1, &ctrl);

	if (lis3_dev.whoami == LIS_DOUBLE_ID)
		val = lis3_12_rates[(ctrl & (CTRL1_DF0 | CTRL1_DF1)) >> 4];
	else
		val = lis3_8_rates[(ctrl & CTRL1_DR) >> 7];

	return sprintf(buf, "%d\n", val);
}