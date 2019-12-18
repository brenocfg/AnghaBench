#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int mainbat_voltage; } ;
struct TYPE_4__ {TYPE_1__ battstat; } ;

/* Variables and functions */
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t battery_voltage_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n",sharpsl_pm.battstat.mainbat_voltage);
}