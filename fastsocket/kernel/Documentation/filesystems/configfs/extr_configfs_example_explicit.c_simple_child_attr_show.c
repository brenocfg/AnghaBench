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
struct simple_child {int storeme; } ;
struct configfs_attribute {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct simple_child* to_simple_child (struct config_item*) ; 

__attribute__((used)) static ssize_t simple_child_attr_show(struct config_item *item,
				      struct configfs_attribute *attr,
				      char *page)
{
	ssize_t count;
	struct simple_child *simple_child = to_simple_child(item);

	count = sprintf(page, "%d\n", simple_child->storeme);

	return count;
}