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
struct device_node {scalar_t__ full_name; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device_node* node; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (char*,scalar_t__) ; 
 TYPE_1__* to_of_device (struct device*) ; 

__attribute__((used)) static int ibmebus_match_path(struct device *dev, void *data)
{
	struct device_node *dn = to_of_device(dev)->node;
	return (dn->full_name &&
		(strcasecmp((char *)data, dn->full_name) == 0));
}