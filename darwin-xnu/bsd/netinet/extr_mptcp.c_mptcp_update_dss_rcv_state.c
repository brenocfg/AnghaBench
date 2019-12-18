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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct tcpcb {int dummy; } ;
struct mptcp_dsn_opt {int /*<<< orphan*/  mdss_data_len; int /*<<< orphan*/  mdss_subflow_seqn; int /*<<< orphan*/  mdss_dsn; } ;
struct mptcb {int /*<<< orphan*/  mpt_rcvnxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTCP_EXTEND_DSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTOHL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTOHS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptcp_update_rcv_state_meat (struct mptcb*,struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mptcb* tptomptp (struct tcpcb*) ; 

void
mptcp_update_dss_rcv_state(struct mptcp_dsn_opt *dss_info, struct tcpcb *tp,
    uint16_t csum)
{
	struct mptcb *mp_tp = tptomptp(tp);
	u_int64_t full_dsn = 0;

	NTOHL(dss_info->mdss_dsn);
	NTOHL(dss_info->mdss_subflow_seqn);
	NTOHS(dss_info->mdss_data_len);

	/* XXX for autosndbuf grow sb here */
	MPTCP_EXTEND_DSN(mp_tp->mpt_rcvnxt, dss_info->mdss_dsn, full_dsn);
	mptcp_update_rcv_state_meat(mp_tp, tp,
	    full_dsn, dss_info->mdss_subflow_seqn, dss_info->mdss_data_len,
	    csum);

}