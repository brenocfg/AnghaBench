#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mem_cgroup_tree_per_zone {int dummy; } ;
struct TYPE_4__ {TYPE_1__** rb_tree_per_node; } ;
struct TYPE_3__ {struct mem_cgroup_tree_per_zone* rb_tree_per_zone; } ;

/* Variables and functions */
 TYPE_2__ soft_limit_tree ; 

__attribute__((used)) static struct mem_cgroup_tree_per_zone *
soft_limit_tree_node_zone(int nid, int zid)
{
	return &soft_limit_tree.rb_tree_per_node[nid]->rb_tree_per_zone[zid];
}