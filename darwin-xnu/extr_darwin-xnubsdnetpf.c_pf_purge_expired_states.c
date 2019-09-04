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
typedef  int /*<<< orphan*/  u_int32_t ;
struct pf_state {scalar_t__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ PFTM_UNLINKED ; 
 struct pf_state* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_state* TAILQ_NEXT (struct pf_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry_list ; 
 int /*<<< orphan*/  pf_free_state (struct pf_state*) ; 
 int /*<<< orphan*/  pf_lock ; 
 scalar_t__ pf_state_expires (struct pf_state*) ; 
 scalar_t__ pf_time_second () ; 
 int /*<<< orphan*/  pf_unlink_state (struct pf_state*) ; 
 int /*<<< orphan*/  state_list ; 

void
pf_purge_expired_states(u_int32_t maxcheck)
{
	static struct pf_state	*cur = NULL;
	struct pf_state		*next;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	while (maxcheck--) {
		/* wrap to start of list when we hit the end */
		if (cur == NULL) {
			cur = TAILQ_FIRST(&state_list);
			if (cur == NULL)
				break;	/* list empty */
		}

		/* get next state, as cur may get deleted */
		next = TAILQ_NEXT(cur, entry_list);

		if (cur->timeout == PFTM_UNLINKED) {
			pf_free_state(cur);
		} else if (pf_state_expires(cur) <= pf_time_second()) {
			/* unlink and free expired state */
			pf_unlink_state(cur);
			pf_free_state(cur);
		}
		cur = next;
	}
}