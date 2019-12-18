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
struct kcore_list {unsigned long addr; size_t size; int type; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kclist_head ; 
 int /*<<< orphan*/  kclist_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void
kclist_add(struct kcore_list *new, void *addr, size_t size, int type)
{
	new->addr = (unsigned long)addr;
	new->size = size;
	new->type = type;

	write_lock(&kclist_lock);
	list_add_tail(&new->list, &kclist_head);
	write_unlock(&kclist_lock);
}