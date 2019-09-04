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
struct exception_action {int /*<<< orphan*/ * label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_exc_free_label (int /*<<< orphan*/ *) ; 

void
mac_exc_free_action_label(struct exception_action *action)
{
	mac_exc_free_label(action->label);
	action->label = NULL;
}