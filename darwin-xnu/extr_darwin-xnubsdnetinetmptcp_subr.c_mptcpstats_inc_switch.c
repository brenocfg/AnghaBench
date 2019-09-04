#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mptsub {int dummy; } ;
struct mptses {TYPE_2__* mpte_itfstats; int /*<<< orphan*/  mpte_subflow_switches; } ;
struct TYPE_4__ {int /*<<< orphan*/  switches; } ;
struct TYPE_3__ {int /*<<< orphan*/  tcps_mp_switches; } ;

/* Variables and functions */
 int mptcp_get_statsindex (TYPE_2__*,struct mptsub const*) ; 
 TYPE_1__ tcpstat ; 

void
mptcpstats_inc_switch(struct mptses *mpte, const struct mptsub *mpts)
{
	int index;

	tcpstat.tcps_mp_switches++;
	mpte->mpte_subflow_switches++;

	index = mptcp_get_statsindex(mpte->mpte_itfstats, mpts);

	if (index != -1)
		mpte->mpte_itfstats[index].switches++;
}