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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u8 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 scalar_t__ TXP_LAST_OFDM ; 
 scalar_t__ TXP_LAST_SISO_MCS_20 ; 
 scalar_t__ TXP_NUM_RATES ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wlc_phy_txpower_sromlimit (struct brcms_phy_pub*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__) ; 

void
wlc_phy_txpower_sromlimit_max_get(struct brcms_phy_pub *ppi, uint chan,
				  u8 *max_txpwr, u8 *min_txpwr)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	u8 tx_pwr_max = 0;
	u8 tx_pwr_min = 255;
	u8 max_num_rate;
	u8 maxtxpwr, mintxpwr, rate, pactrl;

	pactrl = 0;

	max_num_rate = ISNPHY(pi) ? TXP_NUM_RATES :
		       ISLCNPHY(pi) ? (TXP_LAST_SISO_MCS_20 +
				       1) : (TXP_LAST_OFDM + 1);

	for (rate = 0; rate < max_num_rate; rate++) {

		wlc_phy_txpower_sromlimit(ppi, chan, &mintxpwr, &maxtxpwr,
					  rate);

		maxtxpwr = (maxtxpwr > pactrl) ? (maxtxpwr - pactrl) : 0;

		maxtxpwr = (maxtxpwr > 6) ? (maxtxpwr - 6) : 0;

		tx_pwr_max = max(tx_pwr_max, maxtxpwr);
		tx_pwr_min = min(tx_pwr_min, maxtxpwr);
	}
	*max_txpwr = tx_pwr_max;
	*min_txpwr = tx_pwr_min;
}