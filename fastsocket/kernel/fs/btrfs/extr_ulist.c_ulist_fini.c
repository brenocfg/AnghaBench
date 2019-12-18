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
struct ulist {scalar_t__ nodes_alloced; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 scalar_t__ ULIST_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void ulist_fini(struct ulist *ulist)
{
	/*
	 * The first ULIST_SIZE elements are stored inline in struct ulist.
	 * Only if more elements are alocated they need to be freed.
	 */
	if (ulist->nodes_alloced > ULIST_SIZE)
		kfree(ulist->nodes);
	ulist->nodes_alloced = 0;	/* in case ulist_fini is called twice */
}