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
struct net_device {int /*<<< orphan*/  trans_start; struct lbs_private* ml_priv; } ;
struct lbs_private {scalar_t__ currenttxskb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_RSSI ; 
 int /*<<< orphan*/  LBS_DEB_TX ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_host_to_card_done (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  lbs_prepare_and_send_command (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_send_tx_feedback (struct lbs_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lbs_tx_timeout(struct net_device *dev)
{
	struct lbs_private *priv = dev->ml_priv;

	lbs_deb_enter(LBS_DEB_TX);

	lbs_pr_err("tx watch dog timeout\n");

	dev->trans_start = jiffies;

	if (priv->currenttxskb)
		lbs_send_tx_feedback(priv, 0);

	/* XX: Shouldn't we also call into the hw-specific driver
	   to kick it somehow? */
	lbs_host_to_card_done(priv);

	/* More often than not, this actually happens because the
	   firmware has crapped itself -- rather than just a very
	   busy medium. So send a harmless command, and if/when
	   _that_ times out, we'll kick it in the head. */
	lbs_prepare_and_send_command(priv, CMD_802_11_RSSI, 0,
				     0, 0, NULL);

	lbs_deb_leave(LBS_DEB_TX);
}