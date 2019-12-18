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
struct cdc_ncm_ctx {scalar_t__ tx_timer_pending; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdc_ncm_tx_timeout_start (struct cdc_ncm_ctx*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbnet_start_xmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdc_ncm_txpath_bh(unsigned long param)
{
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)param;

	spin_lock_bh(&ctx->mtx);
	if (ctx->tx_timer_pending != 0) {
		ctx->tx_timer_pending--;
		cdc_ncm_tx_timeout_start(ctx);
		spin_unlock_bh(&ctx->mtx);
	} else if (ctx->netdev != NULL) {
		spin_unlock_bh(&ctx->mtx);
		netif_tx_lock_bh(ctx->netdev);
		usbnet_start_xmit(NULL, ctx->netdev);
		netif_tx_unlock_bh(ctx->netdev);
	} else {
		spin_unlock_bh(&ctx->mtx);
	}
}