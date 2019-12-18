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
struct device {int dummy; } ;

/* Variables and functions */
 int attribute_container_add_attrs (struct device*) ; 
 int device_add (struct device*) ; 

int
attribute_container_add_class_device(struct device *classdev)
{
	int error = device_add(classdev);
	if (error)
		return error;
	return attribute_container_add_attrs(classdev);
}