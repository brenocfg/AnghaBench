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
struct enclosure_component {size_t type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** enclosure_type ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 struct enclosure_component* to_enclosure_component (struct device*) ; 

__attribute__((used)) static ssize_t get_component_type(struct device *cdev,
				  struct device_attribute *attr, char *buf)
{
	struct enclosure_component *ecomp = to_enclosure_component(cdev);

	return snprintf(buf, 40, "%s\n", enclosure_type[ecomp->type]);
}