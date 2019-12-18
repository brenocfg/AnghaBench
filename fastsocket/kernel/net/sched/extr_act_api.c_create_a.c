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
struct tc_action {int order; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tc_action* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static struct tc_action *create_a(int i)
{
	struct tc_action *act;

	act = kzalloc(sizeof(*act), GFP_KERNEL);
	if (act == NULL) {
		pr_debug("create_a: failed to alloc!\n");
		return NULL;
	}
	act->order = i;
	return act;
}