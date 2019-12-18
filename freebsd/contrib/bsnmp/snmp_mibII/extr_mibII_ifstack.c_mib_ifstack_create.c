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
struct TYPE_2__ {int len; int /*<<< orphan*/ * subs; } ;
struct mibifstack {TYPE_1__ index; } ;
struct mibif {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT_OBJECT_OID (struct mibifstack*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ticks () ; 
 struct mibifstack* malloc (int) ; 
 int /*<<< orphan*/  mib_ifstack_last_change ; 
 int /*<<< orphan*/  mibifstack_list ; 

int
mib_ifstack_create(const struct mibif *lower, const struct mibif *upper)
{
	struct mibifstack *stack;

	if ((stack = malloc(sizeof(*stack))) == NULL)
		return (-1);

	stack->index.len = 2;
	stack->index.subs[0] = upper ? upper->index : 0;
	stack->index.subs[1] = lower ? lower->index : 0;

	INSERT_OBJECT_OID(stack, &mibifstack_list);

	mib_ifstack_last_change = get_ticks();

	return (0);
}