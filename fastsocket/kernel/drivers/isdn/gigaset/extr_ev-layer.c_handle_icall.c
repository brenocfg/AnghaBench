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
struct cardstate {int commands_pending; int /*<<< orphan*/  dev; } ;
struct bc_state {int dummy; } ;
struct at_state_t {int /*<<< orphan*/  pending_commands; } ;

/* Variables and functions */
#define  ICALL_ACCEPT 130 
#define  ICALL_IGNORE 129 
#define  ICALL_REJECT 128 
 int /*<<< orphan*/  PC_HUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gigaset_isdn_icall (struct at_state_t*) ; 

__attribute__((used)) static void handle_icall(struct cardstate *cs, struct bc_state *bcs,
			 struct at_state_t **p_at_state)
{
	int retval;
	struct at_state_t *at_state = *p_at_state;

	retval = gigaset_isdn_icall(at_state);
	switch (retval) {
	case ICALL_ACCEPT:
		break;
	default:
		dev_err(cs->dev, "internal error: disposition=%d\n", retval);
		/* --v-- fall through --v-- */
	case ICALL_IGNORE:
	case ICALL_REJECT:
		/* hang up actively
		 * Device doc says that would reject the call.
		 * In fact it doesn't.
		 */
		at_state->pending_commands |= PC_HUP;
		cs->commands_pending = 1;
		break;
	}
}