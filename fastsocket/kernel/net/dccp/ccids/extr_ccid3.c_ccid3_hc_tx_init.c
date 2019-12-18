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
struct ccid3_hc_tx_sock {int /*<<< orphan*/  ccid3hctx_no_feedback_timer; int /*<<< orphan*/ * ccid3hctx_hist; int /*<<< orphan*/  ccid3hctx_state; } ;
struct ccid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFRC_SSTATE_NO_SENT ; 
 int /*<<< orphan*/  ccid3_hc_tx_no_feedback_timer ; 
 struct ccid3_hc_tx_sock* ccid_priv (struct ccid*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int ccid3_hc_tx_init(struct ccid *ccid, struct sock *sk)
{
	struct ccid3_hc_tx_sock *hctx = ccid_priv(ccid);

	hctx->ccid3hctx_state = TFRC_SSTATE_NO_SENT;
	hctx->ccid3hctx_hist = NULL;
	setup_timer(&hctx->ccid3hctx_no_feedback_timer,
			ccid3_hc_tx_no_feedback_timer, (unsigned long)sk);

	return 0;
}