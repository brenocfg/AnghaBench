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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ipw_priv {int rates_mask; TYPE_1__* ieee; } ;
struct ipw_fixed_rate {int /*<<< orphan*/  tx_rates; } ;
struct TYPE_2__ {int freq_band; } ;

/* Variables and functions */
 int IEEE_B ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*) ; 
 int /*<<< orphan*/  IPW_MEM_FIXED_OVERRIDE ; 
#define  LIBIPW_52GHZ_BAND 128 
 int LIBIPW_CCK_RATES_MASK ; 
 int LIBIPW_OFDM_RATES_MASK ; 
 int LIBIPW_OFDM_RATE_12MB_MASK ; 
 int LIBIPW_OFDM_RATE_6MB_MASK ; 
 int LIBIPW_OFDM_RATE_9MB_MASK ; 
 int LIBIPW_OFDM_SHIFT_MASK_A ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_set_fixed_rate(struct ipw_priv *priv, int mode)
{
	/* TODO: Verify that this works... */
	struct ipw_fixed_rate fr;
	u32 reg;
	u16 mask = 0;
	u16 new_tx_rates = priv->rates_mask;

	/* Identify 'current FW band' and match it with the fixed
	 * Tx rates */

	switch (priv->ieee->freq_band) {
	case LIBIPW_52GHZ_BAND:	/* A only */
		/* IEEE_A */
		if (priv->rates_mask & ~LIBIPW_OFDM_RATES_MASK) {
			/* Invalid fixed rate mask */
			IPW_DEBUG_WX
			    ("invalid fixed rate mask in ipw_set_fixed_rate\n");
			new_tx_rates = 0;
			break;
		}

		new_tx_rates >>= LIBIPW_OFDM_SHIFT_MASK_A;
		break;

	default:		/* 2.4Ghz or Mixed */
		/* IEEE_B */
		if (mode == IEEE_B) {
			if (new_tx_rates & ~LIBIPW_CCK_RATES_MASK) {
				/* Invalid fixed rate mask */
				IPW_DEBUG_WX
				    ("invalid fixed rate mask in ipw_set_fixed_rate\n");
				new_tx_rates = 0;
			}
			break;
		}

		/* IEEE_G */
		if (new_tx_rates & ~(LIBIPW_CCK_RATES_MASK |
				    LIBIPW_OFDM_RATES_MASK)) {
			/* Invalid fixed rate mask */
			IPW_DEBUG_WX
			    ("invalid fixed rate mask in ipw_set_fixed_rate\n");
			new_tx_rates = 0;
			break;
		}

		if (LIBIPW_OFDM_RATE_6MB_MASK & new_tx_rates) {
			mask |= (LIBIPW_OFDM_RATE_6MB_MASK >> 1);
			new_tx_rates &= ~LIBIPW_OFDM_RATE_6MB_MASK;
		}

		if (LIBIPW_OFDM_RATE_9MB_MASK & new_tx_rates) {
			mask |= (LIBIPW_OFDM_RATE_9MB_MASK >> 1);
			new_tx_rates &= ~LIBIPW_OFDM_RATE_9MB_MASK;
		}

		if (LIBIPW_OFDM_RATE_12MB_MASK & new_tx_rates) {
			mask |= (LIBIPW_OFDM_RATE_12MB_MASK >> 1);
			new_tx_rates &= ~LIBIPW_OFDM_RATE_12MB_MASK;
		}

		new_tx_rates |= mask;
		break;
	}

	fr.tx_rates = cpu_to_le16(new_tx_rates);

	reg = ipw_read32(priv, IPW_MEM_FIXED_OVERRIDE);
	ipw_write_reg32(priv, reg, *(u32 *) & fr);
}