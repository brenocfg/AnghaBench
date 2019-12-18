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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_l_ack_ratio; int /*<<< orphan*/  dccps_mss_cache; } ;
struct ccid2_hc_tx_sock {unsigned int ccid2hctx_ssthresh; int ccid2hctx_rto; int ccid2hctx_rttvar; int ccid2hctx_rpdupack; int /*<<< orphan*/  ccid2hctx_rtotimer; int /*<<< orphan*/  ccid2hctx_last_cong; int /*<<< orphan*/  ccid2hctx_cwnd; } ;
struct ccid {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  ccid2_change_srtt (struct ccid2_hc_tx_sock*,int) ; 
 scalar_t__ ccid2_hc_tx_alloc_seq (struct ccid2_hc_tx_sock*) ; 
 int /*<<< orphan*/  ccid2_hc_tx_check_sanity (struct ccid2_hc_tx_sock*) ; 
 int /*<<< orphan*/  ccid2_hc_tx_rto_expire ; 
 struct ccid2_hc_tx_sock* ccid_priv (struct ccid*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rfc3390_bytes_to_packets (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ccid2_hc_tx_init(struct ccid *ccid, struct sock *sk)
{
	struct ccid2_hc_tx_sock *hctx = ccid_priv(ccid);
	struct dccp_sock *dp = dccp_sk(sk);
	u32 max_ratio;

	/* RFC 4341, 5: initialise ssthresh to arbitrarily high (max) value */
	hctx->ccid2hctx_ssthresh  = ~0U;

	/* Use larger initial windows (RFC 4341, section 5). */
	hctx->ccid2hctx_cwnd = rfc3390_bytes_to_packets(dp->dccps_mss_cache);

	/* Make sure that Ack Ratio is enabled and within bounds. */
	max_ratio = DIV_ROUND_UP(hctx->ccid2hctx_cwnd, 2);
	if (dp->dccps_l_ack_ratio == 0 || dp->dccps_l_ack_ratio > max_ratio)
		dp->dccps_l_ack_ratio = max_ratio;

	/* XXX init ~ to window size... */
	if (ccid2_hc_tx_alloc_seq(hctx))
		return -ENOMEM;

	hctx->ccid2hctx_rto	 = 3 * HZ;
	ccid2_change_srtt(hctx, -1);
	hctx->ccid2hctx_rttvar	 = -1;
	hctx->ccid2hctx_rpdupack = -1;
	hctx->ccid2hctx_last_cong = jiffies;
	setup_timer(&hctx->ccid2hctx_rtotimer, ccid2_hc_tx_rto_expire,
			(unsigned long)sk);

	ccid2_hc_tx_check_sanity(hctx);
	return 0;
}