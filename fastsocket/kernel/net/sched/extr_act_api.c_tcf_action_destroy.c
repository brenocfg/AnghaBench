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
struct tc_action {struct tc_action* next; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* cleanup ) (struct tc_action*,int) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 scalar_t__ ACT_P_DELETED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  kfree (struct tc_action*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct tc_action*,int) ; 

void tcf_action_destroy(struct tc_action *act, int bind)
{
	struct tc_action *a;

	for (a = act; a; a = act) {
		if (a->ops && a->ops->cleanup) {
			if (a->ops->cleanup(a, bind) == ACT_P_DELETED)
				module_put(a->ops->owner);
			act = act->next;
			kfree(a);
		} else {
			/*FIXME: Remove later - catch insertion bugs*/
			WARN(1, "tcf_action_destroy: BUG? destroying NULL ops\n");
			act = act->next;
			kfree(a);
		}
	}
}