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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  ACER_AMW0 130 
#define  ACER_AMW0_V2 129 
#define  ACER_WMID 128 
 TYPE_1__* interface ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t show_interface(struct device *dev, struct device_attribute *attr,
	char *buf)
{
	switch (interface->type) {
	case ACER_AMW0:
		return sprintf(buf, "AMW0\n");
	case ACER_AMW0_V2:
		return sprintf(buf, "AMW0 v2\n");
	case ACER_WMID:
		return sprintf(buf, "WMID\n");
	default:
		return sprintf(buf, "Error!\n");
	}
}