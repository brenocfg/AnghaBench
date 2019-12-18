#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ overflow; } ;
struct TYPE_5__ {TYPE_1__ head; } ;
typedef  TYPE_2__ befs_btree_node ;

/* Variables and functions */
 scalar_t__ befs_bt_inval ; 

__attribute__((used)) static int
befs_leafnode(befs_btree_node * node)
{
	/* all interior nodes (and only interior nodes) have an overflow node */
	if (node->head.overflow == befs_bt_inval)
		return 1;
	else
		return 0;
}