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
struct node {int /*<<< orphan*/  sysdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_cpulist ; 
 int /*<<< orphan*/  attr_cpumap ; 
 int /*<<< orphan*/  attr_distance ; 
 int /*<<< orphan*/  attr_meminfo ; 
 int /*<<< orphan*/  attr_numastat ; 
 int /*<<< orphan*/  hugetlb_unregister_node (struct node*) ; 
 int /*<<< orphan*/  scan_unevictable_unregister_node (struct node*) ; 
 int /*<<< orphan*/  sysdev_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysdev_unregister (int /*<<< orphan*/ *) ; 

void unregister_node(struct node *node)
{
	sysdev_remove_file(&node->sysdev, &attr_cpumap);
	sysdev_remove_file(&node->sysdev, &attr_cpulist);
	sysdev_remove_file(&node->sysdev, &attr_meminfo);
	sysdev_remove_file(&node->sysdev, &attr_numastat);
	sysdev_remove_file(&node->sysdev, &attr_distance);

	scan_unevictable_unregister_node(node);
	hugetlb_unregister_node(node);		/* no-op, if memoryless node */

	sysdev_unregister(&node->sysdev);
}