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
struct label {int dummy; } ;
struct exception_action {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct exception_action*,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  exc_action_label_update ; 

int
mac_exc_update_action_label(struct exception_action *action,
							struct label *newlabel) {
	int error;
	
	MAC_CHECK(exc_action_label_update, action, action->label, newlabel);
	
	return (error);
}