#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int u8 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int min_txpower; int* tx_srom_max_rate_2g; int* hwtxpwr; int* tx_srom_max_rate_5g_mid; int* tx_srom_max_rate_5g_hi; int* tx_srom_max_rate_5g_low; } ;
struct TYPE_3__ {scalar_t__ chan; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__*) ; 
 int BRCMS_TXPWR_DB_FACTOR ; 
 int BRCMS_TXPWR_MAX ; 
 scalar_t__ CH_MAX_2G_CHANNEL ; 
 scalar_t__ FIRST_HIGH_5G_CHAN ; 
 scalar_t__ FIRST_LOW_5G_CHAN ; 
 scalar_t__ FIRST_MID_5G_CHAN ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 scalar_t__ LAST_HIGH_5G_CHAN ; 
 scalar_t__ LAST_LOW_5G_CHAN ; 
 scalar_t__ LAST_MID_5G_CHAN ; 
 int TXP_FIRST_CCK ; 
 int TXP_FIRST_OFDM ; 
 TYPE_1__* chan_info_all ; 
 int /*<<< orphan*/  wlc_phy_txpower_sromlimit_get_nphy (struct brcms_phy*,scalar_t__,int*,int) ; 

void
wlc_phy_txpower_sromlimit(struct brcms_phy_pub *ppi, uint channel, u8 *min_pwr,
			  u8 *max_pwr, int txp_rate_idx)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	uint i;

	*min_pwr = pi->min_txpower * BRCMS_TXPWR_DB_FACTOR;

	if (ISNPHY(pi)) {
		if (txp_rate_idx < 0)
			txp_rate_idx = TXP_FIRST_CCK;
		wlc_phy_txpower_sromlimit_get_nphy(pi, channel, max_pwr,
						   (u8) txp_rate_idx);

	} else if ((channel <= CH_MAX_2G_CHANNEL)) {
		if (txp_rate_idx < 0)
			txp_rate_idx = TXP_FIRST_CCK;
		*max_pwr = pi->tx_srom_max_rate_2g[txp_rate_idx];
	} else {

		*max_pwr = BRCMS_TXPWR_MAX;

		if (txp_rate_idx < 0)
			txp_rate_idx = TXP_FIRST_OFDM;

		for (i = 0; i < ARRAY_SIZE(chan_info_all); i++) {
			if (channel == chan_info_all[i].chan)
				break;
		}

		if (pi->hwtxpwr) {
			*max_pwr = pi->hwtxpwr[i];
		} else {

			if ((i >= FIRST_MID_5G_CHAN) && (i <= LAST_MID_5G_CHAN))
				*max_pwr =
				    pi->tx_srom_max_rate_5g_mid[txp_rate_idx];
			if ((i >= FIRST_HIGH_5G_CHAN)
			    && (i <= LAST_HIGH_5G_CHAN))
				*max_pwr =
				    pi->tx_srom_max_rate_5g_hi[txp_rate_idx];
			if ((i >= FIRST_LOW_5G_CHAN) && (i <= LAST_LOW_5G_CHAN))
				*max_pwr =
				    pi->tx_srom_max_rate_5g_low[txp_rate_idx];
		}
	}
}