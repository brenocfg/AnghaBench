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
struct TYPE_8__ {int ulw_robust; int ulw_dir; struct TYPE_8__* ulw_next; struct TYPE_8__* ulw_prev; int /*<<< orphan*/  ulw_next_result; TYPE_3__* ulw_list; } ;
typedef  TYPE_2__ uu_list_walk_t ;
struct TYPE_7__ {int /*<<< orphan*/  uln_prev; int /*<<< orphan*/  uln_next; } ;
struct TYPE_9__ {TYPE_2__ ul_null_walk; scalar_t__ ul_debug; TYPE_1__ ul_null_node; } ;
typedef  TYPE_3__ uu_list_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int UU_WALK_REVERSE ; 
 int UU_WALK_ROBUST ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
list_walk_init(uu_list_walk_t *wp, uu_list_t *lp, uint32_t flags)
{
	uu_list_walk_t *next, *prev;

	int robust = (flags & UU_WALK_ROBUST);
	int direction = (flags & UU_WALK_REVERSE)? -1 : 1;

	(void) memset(wp, 0, sizeof (*wp));
	wp->ulw_list = lp;
	wp->ulw_robust = robust;
	wp->ulw_dir = direction;
	if (direction > 0)
		wp->ulw_next_result = lp->ul_null_node.uln_next;
	else
		wp->ulw_next_result = lp->ul_null_node.uln_prev;

	if (lp->ul_debug || robust) {
		/*
		 * Add this walker to the list's list of walkers so
		 * uu_list_remove() can advance us if somebody tries to
		 * remove ulw_next_result.
		 */
		wp->ulw_next = next = &lp->ul_null_walk;
		wp->ulw_prev = prev = next->ulw_prev;
		next->ulw_prev = wp;
		prev->ulw_next = wp;
	}
}