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
struct sys_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct node {TYPE_1__ sysdev; } ;
struct cpumask {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NR_CPUS ; 
 int PAGE_SIZE ; 
 int cpulist_scnprintf (char*,int,struct cpumask const*) ; 
 struct cpumask* cpumask_of_node (int /*<<< orphan*/ ) ; 
 int cpumask_scnprintf (char*,int,struct cpumask const*) ; 
 struct node* to_node (struct sys_device*) ; 

__attribute__((used)) static ssize_t node_read_cpumap(struct sys_device *dev, int type, char *buf)
{
	struct node *node_dev = to_node(dev);
	const struct cpumask *mask = cpumask_of_node(node_dev->sysdev.id);
	int len;

	/* 2008/04/07: buf currently PAGE_SIZE, need 9 chars per 32 bits. */
	BUILD_BUG_ON((NR_CPUS/32 * 9) > (PAGE_SIZE-1));

	len = type?
		cpulist_scnprintf(buf, PAGE_SIZE-2, mask) :
		cpumask_scnprintf(buf, PAGE_SIZE-2, mask);
 	buf[len++] = '\n';
 	buf[len] = '\0';
	return len;
}