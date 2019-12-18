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
typedef  scalar_t__ u_int64_t ;
struct TYPE_4__ {scalar_t__ tbr_rate_raw; } ;
struct ifclassq {TYPE_2__ ifcq_tbr; } ;
struct TYPE_3__ {scalar_t__ eff_bw; } ;
struct ifnet {struct ifclassq if_snd; TYPE_1__ if_output_bw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 scalar_t__ IFCQ_TBR_IS_ENABLED (struct ifclassq*) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

u_int64_t
ifnet_output_linkrate(struct ifnet *ifp)
{
	struct ifclassq *ifq = &ifp->if_snd;
	u_int64_t rate;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	rate = ifp->if_output_bw.eff_bw;
	if (IFCQ_TBR_IS_ENABLED(ifq)) {
		u_int64_t tbr_rate = ifp->if_snd.ifcq_tbr.tbr_rate_raw;
		VERIFY(tbr_rate > 0);
		rate = MIN(rate, ifp->if_snd.ifcq_tbr.tbr_rate_raw);
	}

	return (rate);
}