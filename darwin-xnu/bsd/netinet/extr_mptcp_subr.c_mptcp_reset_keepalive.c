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
struct tcpcb {struct mptsub* t_mpsub; } ;
struct mptsub {int /*<<< orphan*/  mpts_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTSF_READ_STALL ; 

void
mptcp_reset_keepalive(struct tcpcb *tp)
{
	struct mptsub *mpts = tp->t_mpsub;

	mpts->mpts_flags &= ~MPTSF_READ_STALL;
}