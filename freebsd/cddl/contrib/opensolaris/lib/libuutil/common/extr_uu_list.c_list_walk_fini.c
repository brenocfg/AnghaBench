#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ulw_next_result; int /*<<< orphan*/ * ulw_list; TYPE_2__* ulw_prev; TYPE_1__* ulw_next; } ;
typedef  TYPE_3__ uu_list_walk_t ;
struct TYPE_6__ {TYPE_1__* ulw_next; } ;
struct TYPE_5__ {TYPE_2__* ulw_prev; } ;

/* Variables and functions */

__attribute__((used)) static void
list_walk_fini(uu_list_walk_t *wp)
{
	/* GLXXX debugging? */
	if (wp->ulw_next != NULL) {
		wp->ulw_next->ulw_prev = wp->ulw_prev;
		wp->ulw_prev->ulw_next = wp->ulw_next;
		wp->ulw_next = NULL;
		wp->ulw_prev = NULL;
	}
	wp->ulw_list = NULL;
	wp->ulw_next_result = NULL;
}