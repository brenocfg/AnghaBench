#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {scalar_t__ flags; TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpol_store_user_nodemask (struct mempolicy const*) ; 
 int nodes_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpol_match_intent(const struct mempolicy *a,
			     const struct mempolicy *b)
{
	if (a->flags != b->flags)
		return 0;
	if (!mpol_store_user_nodemask(a))
		return 1;
	return nodes_equal(a->w.user_nodemask, b->w.user_nodemask);
}