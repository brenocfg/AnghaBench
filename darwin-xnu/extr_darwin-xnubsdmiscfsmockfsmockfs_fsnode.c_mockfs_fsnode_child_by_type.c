#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  TYPE_1__* mockfs_fsnode_t ;
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* child_b; struct TYPE_4__* child_a; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 

int mockfs_fsnode_child_by_type(mockfs_fsnode_t parent, uint8_t type, mockfs_fsnode_t * child)
{
	int rvalue;
	
	rvalue = 0;
	
	if (!parent || !child) {
		rvalue = EINVAL;
		goto done;
	}

	if ((parent->child_a) && (parent->child_a->type == type))
		*child = parent->child_a;
	else if ((parent->child_b) && (parent->child_b->type == type))
		*child = parent->child_b;
	else
		rvalue = ENOENT;

done:
	return rvalue;
}