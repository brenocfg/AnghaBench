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
struct exception_action {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int mac_exc_update_action_label (struct exception_action*,int /*<<< orphan*/ ) ; 

int
mac_exc_inherit_action_label(struct exception_action *parent,
							 struct exception_action *child) {
	return mac_exc_update_action_label(child, parent->label);
}