#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ulw_dir; TYPE_3__* ulw_next_result; } ;
typedef  TYPE_1__ uu_list_walk_t ;
struct TYPE_9__ {struct TYPE_9__* uln_prev; struct TYPE_9__* uln_next; } ;
struct TYPE_8__ {TYPE_3__ ul_null_node; } ;
typedef  TYPE_2__ uu_list_t ;
typedef  TYPE_3__ uu_list_node_impl_t ;

/* Variables and functions */

__attribute__((used)) static uu_list_node_impl_t *
list_walk_advance(uu_list_walk_t *wp, uu_list_t *lp)
{
	uu_list_node_impl_t *np = wp->ulw_next_result;
	uu_list_node_impl_t *next;

	if (np == &lp->ul_null_node)
		return (NULL);

	next = (wp->ulw_dir > 0)? np->uln_next : np->uln_prev;

	wp->ulw_next_result = next;
	return (np);
}