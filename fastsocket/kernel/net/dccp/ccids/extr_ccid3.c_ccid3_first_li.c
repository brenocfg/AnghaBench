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
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct ccid3_hc_rx_sock {scalar_t__ ccid3hcrx_rtt; scalar_t__ ccid3hcrx_x_recv; int ccid3hcrx_s; void* ccid3hcrx_bytes_recv; int /*<<< orphan*/  ccid3hcrx_tstamp_last_feedback; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG (char*) ; 
 scalar_t__ DCCP_FALLBACK_RTT ; 
 int /*<<< orphan*/  DCCP_WARN (char*) ; 
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,int /*<<< orphan*/ ,struct sock*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dccp_role (struct sock*) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_timedelta (int /*<<< orphan*/ ) ; 
 scalar_t__ scaled_div (int,scalar_t__) ; 
 void* scaled_div32 (void*,scalar_t__) ; 
 scalar_t__ tfrc_calc_x_reverse_lookup (void*) ; 

__attribute__((used)) static u32 ccid3_first_li(struct sock *sk)
{
	struct ccid3_hc_rx_sock *hcrx = ccid3_hc_rx_sk(sk);
	u32 x_recv, p, delta;
	u64 fval;

	if (hcrx->ccid3hcrx_rtt == 0) {
		DCCP_WARN("No RTT estimate available, using fallback RTT\n");
		hcrx->ccid3hcrx_rtt = DCCP_FALLBACK_RTT;
	}

	delta = ktime_to_us(net_timedelta(hcrx->ccid3hcrx_tstamp_last_feedback));
	x_recv = scaled_div32(hcrx->ccid3hcrx_bytes_recv, delta);
	if (x_recv == 0) {		/* would also trigger divide-by-zero */
		DCCP_WARN("X_recv==0\n");
		if ((x_recv = hcrx->ccid3hcrx_x_recv) == 0) {
			DCCP_BUG("stored value of X_recv is zero");
			return ~0U;
		}
	}

	fval = scaled_div(hcrx->ccid3hcrx_s, hcrx->ccid3hcrx_rtt);
	fval = scaled_div32(fval, x_recv);
	p = tfrc_calc_x_reverse_lookup(fval);

	ccid3_pr_debug("%s(%p), receive rate=%u bytes/s, implied "
		       "loss rate=%u\n", dccp_role(sk), sk, x_recv, p);

	return p == 0 ? ~0U : scaled_div(1, p);
}