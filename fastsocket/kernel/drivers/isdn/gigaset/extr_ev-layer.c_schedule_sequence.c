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
struct cardstate {int cur_at_seq; } ;
struct at_state_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSP_INIT ; 
 int /*<<< orphan*/  gigaset_add_event (struct cardstate*,struct at_state_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void schedule_sequence(struct cardstate *cs,
			      struct at_state_t *at_state, int sequence)
{
	cs->cur_at_seq = sequence;
	gigaset_add_event(cs, at_state, RSP_INIT, NULL, sequence, NULL);
}