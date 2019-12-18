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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  channel; } ;
struct iwl_rxon_context {TYPE_1__ staging; } ;
struct iwl_priv {int band; } ;
struct ieee80211_channel {int band; scalar_t__ hw_value; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  RXON_FLG_BAND_24G_MSK ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

void iwl_set_rxon_channel(struct iwl_priv *priv, struct ieee80211_channel *ch,
			 struct iwl_rxon_context *ctx)
{
	enum ieee80211_band band = ch->band;
	u16 channel = ch->hw_value;

	if ((le16_to_cpu(ctx->staging.channel) == channel) &&
	    (priv->band == band))
		return;

	ctx->staging.channel = cpu_to_le16(channel);
	if (band == IEEE80211_BAND_5GHZ)
		ctx->staging.flags &= ~RXON_FLG_BAND_24G_MSK;
	else
		ctx->staging.flags |= RXON_FLG_BAND_24G_MSK;

	priv->band = band;

	IWL_DEBUG_INFO(priv, "Staging channel set to %d [%d]\n", channel, band);

}