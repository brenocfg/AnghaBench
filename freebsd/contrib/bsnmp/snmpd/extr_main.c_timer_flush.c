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
struct timer {struct lmodule* owner; } ;
struct lmodule {int dummy; } ;

/* Variables and functions */
 struct timer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct timer* LIST_NEXT (struct timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  timer_list ; 
 int /*<<< orphan*/  timer_stop (struct timer*) ; 

__attribute__((used)) static void
timer_flush(struct lmodule *mod)
{
	struct timer *t, *t1;

	t = LIST_FIRST(&timer_list);
	while (t != NULL) {
		t1 = LIST_NEXT(t, link);
		if (t->owner == mod)
			timer_stop(t);
		t = t1;
	}
}