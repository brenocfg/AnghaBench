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
struct resource {scalar_t__ start; scalar_t__ end; scalar_t__ flags; int /*<<< orphan*/  name; struct resource* sibling; } ;
typedef  scalar_t__ resource_size_t ;
struct TYPE_2__ {struct resource* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__ iomem_resource ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_lock ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int find_next_system_ram(struct resource *res, char *name)
{
	resource_size_t start, end;
	struct resource *p;

	BUG_ON(!res);

	start = res->start;
	end = res->end;
	BUG_ON(start >= end);

	read_lock(&resource_lock);
	for (p = iomem_resource.child; p ; p = p->sibling) {
		/* system ram is just marked as IORESOURCE_MEM */
		if (p->flags != res->flags)
			continue;
		if (name && strcmp(p->name, name))
			continue;
		if (p->start > end) {
			p = NULL;
			break;
		}
		if ((p->end >= start) && (p->start < end))
			break;
	}
	read_unlock(&resource_lock);
	if (!p)
		return -1;
	/* copy data */
	if (res->start < p->start)
		res->start = p->start;
	if (res->end > p->end)
		res->end = p->end;
	return 0;
}