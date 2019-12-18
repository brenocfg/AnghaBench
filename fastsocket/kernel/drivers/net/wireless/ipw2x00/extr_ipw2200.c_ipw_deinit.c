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
struct ipw_priv {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_DISASSOCIATING ; 
 int STATUS_INIT ; 
 int STATUS_SCANNING ; 
 int /*<<< orphan*/  ipw_abort_scan (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_disassociate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_led_shutdown (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_send_card_disable (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ipw_deinit(struct ipw_priv *priv)
{
	int i;

	if (priv->status & STATUS_SCANNING) {
		IPW_DEBUG_INFO("Aborting scan during shutdown.\n");
		ipw_abort_scan(priv);
	}

	if (priv->status & STATUS_ASSOCIATED) {
		IPW_DEBUG_INFO("Disassociating during shutdown.\n");
		ipw_disassociate(priv);
	}

	ipw_led_shutdown(priv);

	/* Wait up to 1s for status to change to not scanning and not
	 * associated (disassociation can take a while for a ful 802.11
	 * exchange */
	for (i = 1000; i && (priv->status &
			     (STATUS_DISASSOCIATING |
			      STATUS_ASSOCIATED | STATUS_SCANNING)); i--)
		udelay(10);

	if (priv->status & (STATUS_DISASSOCIATING |
			    STATUS_ASSOCIATED | STATUS_SCANNING))
		IPW_DEBUG_INFO("Still associated or scanning...\n");
	else
		IPW_DEBUG_INFO("Took %dms to de-init\n", 1000 - i);

	/* Attempt to disable the card */
	ipw_send_card_disable(priv, 0);

	priv->status &= ~STATUS_INIT;
}