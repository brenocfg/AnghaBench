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
struct configfs_attribute {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct configfs_attribute**) ; 
 int /*<<< orphan*/  BUG () ; 
 struct configfs_attribute** o2nm_node_attrs ; 

__attribute__((used)) static int o2nm_attr_index(struct configfs_attribute *attr)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(o2nm_node_attrs); i++) {
		if (attr == o2nm_node_attrs[i])
			return i;
	}
	BUG();
	return 0;
}