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
struct ics932s401_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int calculate_pci_freq (struct ics932s401_data*) ; 
 struct ics932s401_data* ics932s401_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_pci_clock(struct device *dev,
			      struct device_attribute *devattr,
			      char *buf)
{
	struct ics932s401_data *data = ics932s401_update_device(dev);

	return sprintf(buf, "%d\n", calculate_pci_freq(data));
}