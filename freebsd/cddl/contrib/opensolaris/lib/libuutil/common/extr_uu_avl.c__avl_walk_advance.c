#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ uaw_dir; void* uaw_next_result; } ;
typedef  TYPE_1__ uu_avl_walk_t ;
struct TYPE_6__ {int /*<<< orphan*/  ua_tree; } ;
typedef  TYPE_2__ uu_avl_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 void* AVL_NEXT (int /*<<< orphan*/ *,void*) ; 
 void* AVL_PREV (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void *
_avl_walk_advance(uu_avl_walk_t *wp, uu_avl_t *ap)
{
	void *np = wp->uaw_next_result;

	avl_tree_t *t = &ap->ua_tree;

	if (np == NULL)
		return (NULL);

	wp->uaw_next_result = (wp->uaw_dir > 0)? AVL_NEXT(t, np) :
	    AVL_PREV(t, np);

	return (np);
}