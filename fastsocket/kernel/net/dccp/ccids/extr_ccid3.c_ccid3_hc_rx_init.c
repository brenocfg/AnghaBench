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
struct sock {int dummy; } ;
struct ccid3_hc_rx_sock {int /*<<< orphan*/  ccid3hcrx_hist; int /*<<< orphan*/  ccid3hcrx_li_hist; int /*<<< orphan*/  ccid3hcrx_state; } ;
struct ccid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFRC_RSTATE_NO_DATA ; 
 struct ccid3_hc_rx_sock* ccid_priv (struct ccid*) ; 
 int /*<<< orphan*/  tfrc_lh_init (int /*<<< orphan*/ *) ; 
 int tfrc_rx_hist_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccid3_hc_rx_init(struct ccid *ccid, struct sock *sk)
{
	struct ccid3_hc_rx_sock *hcrx = ccid_priv(ccid);

	hcrx->ccid3hcrx_state = TFRC_RSTATE_NO_DATA;
	tfrc_lh_init(&hcrx->ccid3hcrx_li_hist);
	return tfrc_rx_hist_alloc(&hcrx->ccid3hcrx_hist);
}