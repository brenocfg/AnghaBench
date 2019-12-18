#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct entry {int /*<<< orphan*/  cl; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,void*,void*) ;} ;
struct TYPE_3__ {struct TYPE_3__* link; struct entry* x; } ;
typedef  TYPE_1__* List ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,void*) ; 

void apply(List event, void *arg1, void *arg2) {
	if (event) {
		List lp = event;
		do {
			struct entry *p = lp->x;
			(*p->func)(p->cl, arg1, arg2);
			lp = lp->link;
		} while (lp != event);
	}
}