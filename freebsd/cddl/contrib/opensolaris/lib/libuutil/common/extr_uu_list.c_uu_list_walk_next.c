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
struct TYPE_4__ {int /*<<< orphan*/ * ulw_list; } ;
typedef  TYPE_1__ uu_list_walk_t ;
typedef  int /*<<< orphan*/  uu_list_t ;
typedef  int /*<<< orphan*/  uu_list_node_impl_t ;

/* Variables and functions */
 void* NODE_TO_ELEM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_walk_advance (TYPE_1__*,int /*<<< orphan*/ *) ; 

void *
uu_list_walk_next(uu_list_walk_t *wp)
{
	uu_list_t *lp = wp->ulw_list;
	uu_list_node_impl_t *np = list_walk_advance(wp, lp);

	if (np == NULL)
		return (NULL);

	return (NODE_TO_ELEM(lp, np));
}