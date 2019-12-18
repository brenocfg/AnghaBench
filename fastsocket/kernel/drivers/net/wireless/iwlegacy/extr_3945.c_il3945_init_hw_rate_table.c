#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sta_supp_rates; } ;
struct il_priv {int band; TYPE_1__ _3945; int /*<<< orphan*/  retry_rate; } ;
struct il3945_rate_scaling_info {int next_rate_idx; int /*<<< orphan*/  try_cnt; int /*<<< orphan*/  rate_n_flags; } ;
struct il3945_rate_scaling_cmd {int table_id; struct il3945_rate_scaling_info* table; int /*<<< orphan*/  reserved; } ;
typedef  int /*<<< orphan*/  rate_cmd ;
struct TYPE_5__ {int table_rs_idx; int /*<<< orphan*/  plcp; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  C_RATE_SCALE ; 
 int /*<<< orphan*/  D_RATE (char*) ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 int IL_FIRST_CCK_RATE ; 
 size_t IL_FIRST_OFDM_RATE ; 
 int IL_OFDM_RATES_MASK ; 
 int RATE_11M_IDX_TBL ; 
 size_t RATE_12M_IDX_TBL ; 
 int RATE_1M_IDX_TBL ; 
 int RATE_54M_IDX_TBL ; 
 int RATE_5M_IDX_TBL ; 
 size_t RATE_6M_IDX_TBL ; 
 int RATE_9M_IDX_TBL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int il3945_get_prev_ieee_rate (int) ; 
 TYPE_2__* il3945_rates ; 
 int /*<<< orphan*/  il_is_associated (struct il_priv*) ; 
 int il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il3945_rate_scaling_cmd*) ; 

int
il3945_init_hw_rate_table(struct il_priv *il)
{
	int rc, i, idx, prev_idx;
	struct il3945_rate_scaling_cmd rate_cmd = {
		.reserved = {0, 0, 0},
	};
	struct il3945_rate_scaling_info *table = rate_cmd.table;

	for (i = 0; i < ARRAY_SIZE(il3945_rates); i++) {
		idx = il3945_rates[i].table_rs_idx;

		table[idx].rate_n_flags = cpu_to_le16(il3945_rates[i].plcp);
		table[idx].try_cnt = il->retry_rate;
		prev_idx = il3945_get_prev_ieee_rate(i);
		table[idx].next_rate_idx = il3945_rates[prev_idx].table_rs_idx;
	}

	switch (il->band) {
	case IEEE80211_BAND_5GHZ:
		D_RATE("Select A mode rate scale\n");
		/* If one of the following CCK rates is used,
		 * have it fall back to the 6M OFDM rate */
		for (i = RATE_1M_IDX_TBL; i <= RATE_11M_IDX_TBL; i++)
			table[i].next_rate_idx =
			    il3945_rates[IL_FIRST_OFDM_RATE].table_rs_idx;

		/* Don't fall back to CCK rates */
		table[RATE_12M_IDX_TBL].next_rate_idx = RATE_9M_IDX_TBL;

		/* Don't drop out of OFDM rates */
		table[RATE_6M_IDX_TBL].next_rate_idx =
		    il3945_rates[IL_FIRST_OFDM_RATE].table_rs_idx;
		break;

	case IEEE80211_BAND_2GHZ:
		D_RATE("Select B/G mode rate scale\n");
		/* If an OFDM rate is used, have it fall back to the
		 * 1M CCK rates */

		if (!(il->_3945.sta_supp_rates & IL_OFDM_RATES_MASK) &&
		    il_is_associated(il)) {

			idx = IL_FIRST_CCK_RATE;
			for (i = RATE_6M_IDX_TBL; i <= RATE_54M_IDX_TBL; i++)
				table[i].next_rate_idx =
				    il3945_rates[idx].table_rs_idx;

			idx = RATE_11M_IDX_TBL;
			/* CCK shouldn't fall back to OFDM... */
			table[idx].next_rate_idx = RATE_5M_IDX_TBL;
		}
		break;

	default:
		WARN_ON(1);
		break;
	}

	/* Update the rate scaling for control frame Tx */
	rate_cmd.table_id = 0;
	rc = il_send_cmd_pdu(il, C_RATE_SCALE, sizeof(rate_cmd), &rate_cmd);
	if (rc)
		return rc;

	/* Update the rate scaling for data frame Tx */
	rate_cmd.table_id = 1;
	return il_send_cmd_pdu(il, C_RATE_SCALE, sizeof(rate_cmd), &rate_cmd);
}