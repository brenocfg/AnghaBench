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
struct ipw_priv {int config; int channel; int bssid; int capability; int rates_mask; int /*<<< orphan*/  essid_len; int /*<<< orphan*/  essid; } ;

/* Variables and functions */
 int CAP_PRIVACY_ON ; 
 int CFG_STATIC_BSSID ; 
 int CFG_STATIC_CHANNEL ; 
 int CFG_STATIC_ESSID ; 
 int /*<<< orphan*/  DECLARE_SSID_BUF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 int print_ssid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssid ; 

__attribute__((used)) static void ipw_debug_config(struct ipw_priv *priv)
{
	DECLARE_SSID_BUF(ssid);
	IPW_DEBUG_INFO("Scan completed, no valid APs matched "
		       "[CFG 0x%08X]\n", priv->config);
	if (priv->config & CFG_STATIC_CHANNEL)
		IPW_DEBUG_INFO("Channel locked to %d\n", priv->channel);
	else
		IPW_DEBUG_INFO("Channel unlocked.\n");
	if (priv->config & CFG_STATIC_ESSID)
		IPW_DEBUG_INFO("ESSID locked to '%s'\n",
			       print_ssid(ssid, priv->essid, priv->essid_len));
	else
		IPW_DEBUG_INFO("ESSID unlocked.\n");
	if (priv->config & CFG_STATIC_BSSID)
		IPW_DEBUG_INFO("BSSID locked to %pM\n", priv->bssid);
	else
		IPW_DEBUG_INFO("BSSID unlocked.\n");
	if (priv->capability & CAP_PRIVACY_ON)
		IPW_DEBUG_INFO("PRIVACY on\n");
	else
		IPW_DEBUG_INFO("PRIVACY off\n");
	IPW_DEBUG_INFO("RATE MASK: 0x%08X\n", priv->rates_mask);
}