#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ipw_priv {scalar_t__ channel; int status; TYPE_1__* ieee; int /*<<< orphan*/  config; } ;
struct TYPE_2__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_STATIC_CHANNEL ; 
 int /*<<< orphan*/  IPW_DEBUG_ASSOC (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*,...) ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int STATUS_SCANNING ; 
 int /*<<< orphan*/  ipw_abort_scan (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_associate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_disassociate (struct ipw_priv*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ipw_set_channel(struct ipw_priv *priv, u8 channel)
{
	if (channel == 0) {
		IPW_DEBUG_INFO("Setting channel to ANY (0)\n");
		priv->config &= ~CFG_STATIC_CHANNEL;
		IPW_DEBUG_ASSOC("Attempting to associate with new "
				"parameters.\n");
		ipw_associate(priv);
		return 0;
	}

	priv->config |= CFG_STATIC_CHANNEL;

	if (priv->channel == channel) {
		IPW_DEBUG_INFO("Request to set channel to current value (%d)\n",
			       channel);
		return 0;
	}

	IPW_DEBUG_INFO("Setting channel to %i\n", (int)channel);
	priv->channel = channel;

#ifdef CONFIG_IPW2200_MONITOR
	if (priv->ieee->iw_mode == IW_MODE_MONITOR) {
		int i;
		if (priv->status & STATUS_SCANNING) {
			IPW_DEBUG_SCAN("Scan abort triggered due to "
				       "channel change.\n");
			ipw_abort_scan(priv);
		}

		for (i = 1000; i && (priv->status & STATUS_SCANNING); i--)
			udelay(10);

		if (priv->status & STATUS_SCANNING)
			IPW_DEBUG_SCAN("Still scanning...\n");
		else
			IPW_DEBUG_SCAN("Took %dms to abort current scan\n",
				       1000 - i);

		return 0;
	}
#endif				/* CONFIG_IPW2200_MONITOR */

	/* Network configuration changed -- force [re]association */
	IPW_DEBUG_ASSOC("[re]association triggered due to channel change.\n");
	if (!ipw_disassociate(priv))
		ipw_associate(priv);

	return 0;
}