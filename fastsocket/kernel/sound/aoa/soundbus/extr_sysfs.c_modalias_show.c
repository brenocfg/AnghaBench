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
struct of_device {TYPE_1__* node; } ;
struct soundbus_dev {scalar_t__* modalias; struct of_device ofdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; char* type; } ;

/* Variables and functions */
 int sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__*,int) ; 
 int strlen (char*) ; 
 struct soundbus_dev* to_soundbus_device (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct soundbus_dev *sdev = to_soundbus_device(dev);
	struct of_device *of = &sdev->ofdev;
	int length;

	if (*sdev->modalias) {
		strlcpy(buf, sdev->modalias, sizeof(sdev->modalias) + 1);
		strcat(buf, "\n");
		length = strlen(buf);
	} else {
		length = sprintf(buf, "of:N%sT%s\n",
				 of->node->name, of->node->type);
	}

	return length;
}