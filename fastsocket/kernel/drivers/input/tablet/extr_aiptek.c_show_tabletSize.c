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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct aiptek {TYPE_1__* inputdev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int* absmax; } ;

/* Variables and functions */
 size_t ABS_X ; 
 size_t ABS_Y ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static ssize_t show_tabletSize(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "%dx%d\n",
			aiptek->inputdev->absmax[ABS_X] + 1,
			aiptek->inputdev->absmax[ABS_Y] + 1);
}