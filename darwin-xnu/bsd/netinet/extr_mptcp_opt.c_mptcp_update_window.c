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
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct mptcb {scalar_t__ mpt_sndwl1; scalar_t__ mpt_sndwl2; scalar_t__ mpt_sndwnd; } ;

/* Variables and functions */
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
mptcp_update_window(struct mptcb *mp_tp, u_int64_t ack, u_int64_t seq, u_int32_t tiwin)
{
	if (SEQ_LT(mp_tp->mpt_sndwl1, seq) ||
	    (mp_tp->mpt_sndwl1 == seq &&
	     (SEQ_LT(mp_tp->mpt_sndwl2, ack) ||
	      (mp_tp->mpt_sndwl2 == ack && tiwin > mp_tp->mpt_sndwnd)))) {
		mp_tp->mpt_sndwnd = tiwin;
		mp_tp->mpt_sndwl1 = seq;
		mp_tp->mpt_sndwl2 = ack;
	}
}