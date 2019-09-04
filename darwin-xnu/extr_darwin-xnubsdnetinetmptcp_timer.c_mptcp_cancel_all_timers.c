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
struct mptcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTT_FASTCLOSE ; 
 int /*<<< orphan*/  MPTT_REXMT ; 
 int /*<<< orphan*/  MPTT_TW ; 
 int /*<<< orphan*/  mptcp_cancel_timer (struct mptcb*,int /*<<< orphan*/ ) ; 

void
mptcp_cancel_all_timers(struct mptcb *mp_tp)
{
	mptcp_cancel_timer(mp_tp, MPTT_REXMT);
	mptcp_cancel_timer(mp_tp, MPTT_TW);
	mptcp_cancel_timer(mp_tp, MPTT_FASTCLOSE);
}