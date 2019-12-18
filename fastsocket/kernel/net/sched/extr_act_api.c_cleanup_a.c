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
struct tc_action {struct tc_action* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tc_action*) ; 

__attribute__((used)) static void cleanup_a(struct tc_action *act)
{
	struct tc_action *a;

	for (a = act; a; a = act) {
		act = a->next;
		kfree(a);
	}
}