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
typedef  int u64 ;
struct ccid3_hc_tx_sock {int ccid3hctx_t_ipi; int ccid3hctx_x; scalar_t__ ccid3hctx_s; int /*<<< orphan*/  ccid3hctx_delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFRC_OPSYS_HALF_TIME_GRAN ; 
 int /*<<< orphan*/  ccid3_pr_debug (char*,int,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int scaled_div32 (int,int) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void ccid3_update_send_interval(struct ccid3_hc_tx_sock *hctx)
{
	/* Calculate new t_ipi = s / X_inst (X_inst is in 64 * bytes/second) */
	hctx->ccid3hctx_t_ipi = scaled_div32(((u64)hctx->ccid3hctx_s) << 6,
					     hctx->ccid3hctx_x);

	/* Calculate new delta by delta = min(t_ipi / 2, t_gran / 2) */
	hctx->ccid3hctx_delta = min_t(u32, hctx->ccid3hctx_t_ipi / 2,
					   TFRC_OPSYS_HALF_TIME_GRAN);

	ccid3_pr_debug("t_ipi=%u, delta=%u, s=%u, X=%u\n",
		       hctx->ccid3hctx_t_ipi, hctx->ccid3hctx_delta,
		       hctx->ccid3hctx_s, (unsigned)(hctx->ccid3hctx_x >> 6));

}