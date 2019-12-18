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
struct w83627hf_data {int /*<<< orphan*/  vrm; int /*<<< orphan*/  vid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 scalar_t__ vid_from_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct w83627hf_data* w83627hf_update_device (struct device*) ; 

__attribute__((used)) static ssize_t
show_vid_reg(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct w83627hf_data *data = w83627hf_update_device(dev);
	return sprintf(buf, "%ld\n", (long) vid_from_reg(data->vid, data->vrm));
}