#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; int /*<<< orphan*/ * cls; } ;
struct node {TYPE_1__ sysdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_cpulist ; 
 int /*<<< orphan*/  attr_cpumap ; 
 int /*<<< orphan*/  attr_distance ; 
 int /*<<< orphan*/  attr_meminfo ; 
 int /*<<< orphan*/  attr_numastat ; 
 int /*<<< orphan*/  compaction_register_node (struct node*) ; 
 int /*<<< orphan*/  hugetlb_register_node (struct node*) ; 
 int /*<<< orphan*/  node_class ; 
 int /*<<< orphan*/  scan_unevictable_register_node (struct node*) ; 
 int /*<<< orphan*/  sysdev_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sysdev_register (TYPE_1__*) ; 

int register_node(struct node *node, int num, struct node *parent)
{
	int error;

	node->sysdev.id = num;
	node->sysdev.cls = &node_class;
	error = sysdev_register(&node->sysdev);

	if (!error){
		sysdev_create_file(&node->sysdev, &attr_cpumap);
		sysdev_create_file(&node->sysdev, &attr_cpulist);
		sysdev_create_file(&node->sysdev, &attr_meminfo);
		sysdev_create_file(&node->sysdev, &attr_numastat);
		sysdev_create_file(&node->sysdev, &attr_distance);

		scan_unevictable_register_node(node);

		hugetlb_register_node(node);

		compaction_register_node(node);
	}
	return error;
}