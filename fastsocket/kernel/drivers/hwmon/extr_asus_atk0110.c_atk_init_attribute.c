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
typedef  int /*<<< orphan*/  sysfs_show_func ;
struct TYPE_2__ {char* name; int mode; } ;
struct device_attribute {int /*<<< orphan*/ * store; int /*<<< orphan*/  show; TYPE_1__ attr; } ;

/* Variables and functions */

__attribute__((used)) static void atk_init_attribute(struct device_attribute *attr, char *name,
		sysfs_show_func show)
{
	attr->attr.name = name;
	attr->attr.mode = 0444;
	attr->show = show;
	attr->store = NULL;
}