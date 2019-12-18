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
struct sci_remote_node_context {int destination_state; int /*<<< orphan*/  user_cookie; int /*<<< orphan*/  user_callback; } ;

/* Variables and functions */
#define  RNC_DEST_FINAL 130 
#define  RNC_DEST_READY 129 
#define  RNC_DEST_SUSPENDED_RESUME 128 
 int RNC_DEST_UNSPECIFIED ; 
 int /*<<< orphan*/  sci_remote_node_context_resume (struct sci_remote_node_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_remote_node_context_continue_state_transitions(struct sci_remote_node_context *rnc)
{
	switch (rnc->destination_state) {
	case RNC_DEST_READY:
	case RNC_DEST_SUSPENDED_RESUME:
		rnc->destination_state = RNC_DEST_READY;
		/* Fall through... */
	case RNC_DEST_FINAL:
		sci_remote_node_context_resume(rnc, rnc->user_callback,
					       rnc->user_cookie);
		break;
	default:
		rnc->destination_state = RNC_DEST_UNSPECIFIED;
		break;
	}
}