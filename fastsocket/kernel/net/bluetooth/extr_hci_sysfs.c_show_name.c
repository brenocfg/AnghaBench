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
struct hci_dev {char* dev_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct hci_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_name(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct hci_dev *hdev = dev_get_drvdata(dev);
	char name[249];
	int i;

	for (i = 0; i < 248; i++)
		name[i] = hdev->dev_name[i];

	name[248] = '\0';
	return sprintf(buf, "%s\n", name);
}