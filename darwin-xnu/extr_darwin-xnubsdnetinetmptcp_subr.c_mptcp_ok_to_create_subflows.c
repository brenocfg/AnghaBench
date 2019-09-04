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
struct mptcb {scalar_t__ mpt_state; int mpt_flags; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int MPTCPF_FALLBACK_TO_TCP ; 
 scalar_t__ MPTCPS_ESTABLISHED ; 
 scalar_t__ MPTCPS_FIN_WAIT_1 ; 

__attribute__((used)) static boolean_t
mptcp_ok_to_create_subflows(struct mptcb *mp_tp)
{
	return (mp_tp->mpt_state >= MPTCPS_ESTABLISHED &&
		mp_tp->mpt_state < MPTCPS_FIN_WAIT_1 &&
		!(mp_tp->mpt_flags & MPTCPF_FALLBACK_TO_TCP));
}