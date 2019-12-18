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
struct mptcb {scalar_t__ mpt_state; int /*<<< orphan*/  mpt_mpte; } ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ MPTCPS_CLOSE_WAIT ; 
 int /*<<< orphan*/  mpte_lock_assert_held (int /*<<< orphan*/ ) ; 

boolean_t
mptcp_ok_to_keepalive(struct mptcb *mp_tp)
{
	boolean_t ret = 1;
	mpte_lock_assert_held(mp_tp->mpt_mpte);

	if (mp_tp->mpt_state >= MPTCPS_CLOSE_WAIT) {
		ret = 0;
	}
	return (ret);
}