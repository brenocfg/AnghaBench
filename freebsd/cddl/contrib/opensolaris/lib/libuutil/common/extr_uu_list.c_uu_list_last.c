#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* uln_prev; } ;
struct TYPE_6__ {TYPE_2__ ul_null_node; } ;
typedef  TYPE_1__ uu_list_t ;
typedef  TYPE_2__ uu_list_node_impl_t ;

/* Variables and functions */
 void* NODE_TO_ELEM (TYPE_1__*,TYPE_2__*) ; 

void *
uu_list_last(uu_list_t *lp)
{
	uu_list_node_impl_t *n = lp->ul_null_node.uln_prev;
	if (n == &lp->ul_null_node)
		return (NULL);
	return (NODE_TO_ELEM(lp, n));
}