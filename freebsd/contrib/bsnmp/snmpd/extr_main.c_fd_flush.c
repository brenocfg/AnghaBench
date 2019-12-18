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
struct lmodule {int dummy; } ;
struct fdesc {struct lmodule* owner; } ;

/* Variables and functions */
 struct fdesc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct fdesc* LIST_NEXT (struct fdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_deselect (struct fdesc*) ; 
 int /*<<< orphan*/  fdesc_list ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
fd_flush(struct lmodule *mod)
{
	struct fdesc *t, *t1;

	t = LIST_FIRST(&fdesc_list);
	while (t != NULL) {
		t1 = LIST_NEXT(t, link);
		if (t->owner == mod)
			fd_deselect(t);
		t = t1;
	}
}