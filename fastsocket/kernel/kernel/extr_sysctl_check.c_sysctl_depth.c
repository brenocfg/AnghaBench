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
struct ctl_table {struct ctl_table* parent; } ;

/* Variables and functions */

__attribute__((used)) static int sysctl_depth(struct ctl_table *table)
{
	struct ctl_table *tmp;
	int depth;

	depth = 0;
	for (tmp = table; tmp->parent; tmp = tmp->parent)
		depth++;

	return depth;
}