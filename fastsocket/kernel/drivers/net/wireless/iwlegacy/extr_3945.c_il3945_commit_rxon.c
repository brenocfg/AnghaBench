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
struct il3945_rxon_cmd {int filter_flags; int flags; scalar_t__ reserved5; scalar_t__ reserved4; int /*<<< orphan*/  bssid_addr; int /*<<< orphan*/  channel; } ;
struct il_priv {int /*<<< orphan*/  tx_power_next; struct il3945_rxon_cmd active; int /*<<< orphan*/  status; int /*<<< orphan*/  staging; } ;
struct TYPE_2__ {int /*<<< orphan*/  sw_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_RXON ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int RXON_FILTER_ASSOC_MSK ; 
 int RXON_FLG_ANT_SEL_MSK ; 
 int RXON_FLG_DIS_DIV_MSK ; 
 int RXON_FLG_TSF2HOST_MSK ; 
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int il3945_get_antenna_flags (struct il_priv*) ; 
 int il3945_init_hw_rate_table (struct il_priv*) ; 
 TYPE_1__ il3945_mod_params ; 
 int il_check_rxon_cmd (struct il_priv*) ; 
 int /*<<< orphan*/  il_clear_ucode_stations (struct il_priv*) ; 
 int /*<<< orphan*/  il_full_rxon_required (struct il_priv*) ; 
 int /*<<< orphan*/  il_is_alive (struct il_priv*) ; 
 scalar_t__ il_is_associated (struct il_priv*) ; 
 int /*<<< orphan*/  il_restore_stations (struct il_priv*) ; 
 int il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il3945_rxon_cmd*) ; 
 int il_send_rxon_assoc (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_rxon_hwcrypto (struct il_priv*,int) ; 
 int il_set_tx_power (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct il3945_rxon_cmd*,struct il3945_rxon_cmd*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
il3945_commit_rxon(struct il_priv *il)
{
	/* cast away the const for active_rxon in this function */
	struct il3945_rxon_cmd *active_rxon = (void *)&il->active;
	struct il3945_rxon_cmd *staging_rxon = (void *)&il->staging;
	int rc = 0;
	bool new_assoc = !!(staging_rxon->filter_flags & RXON_FILTER_ASSOC_MSK);

	if (test_bit(S_EXIT_PENDING, &il->status))
		return -EINVAL;

	if (!il_is_alive(il))
		return -1;

	/* always get timestamp with Rx frame */
	staging_rxon->flags |= RXON_FLG_TSF2HOST_MSK;

	/* select antenna */
	staging_rxon->flags &= ~(RXON_FLG_DIS_DIV_MSK | RXON_FLG_ANT_SEL_MSK);
	staging_rxon->flags |= il3945_get_antenna_flags(il);

	rc = il_check_rxon_cmd(il);
	if (rc) {
		IL_ERR("Invalid RXON configuration.  Not committing.\n");
		return -EINVAL;
	}

	/* If we don't need to send a full RXON, we can use
	 * il3945_rxon_assoc_cmd which is used to reconfigure filter
	 * and other flags for the current radio configuration. */
	if (!il_full_rxon_required(il)) {
		rc = il_send_rxon_assoc(il);
		if (rc) {
			IL_ERR("Error setting RXON_ASSOC "
			       "configuration (%d).\n", rc);
			return rc;
		}

		memcpy(active_rxon, staging_rxon, sizeof(*active_rxon));
		/*
		 * We do not commit tx power settings while channel changing,
		 * do it now if tx power changed.
		 */
		il_set_tx_power(il, il->tx_power_next, false);
		return 0;
	}

	/* If we are currently associated and the new config requires
	 * an RXON_ASSOC and the new config wants the associated mask enabled,
	 * we must clear the associated from the active configuration
	 * before we apply the new config */
	if (il_is_associated(il) && new_assoc) {
		D_INFO("Toggling associated bit on current RXON\n");
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;

		/*
		 * reserved4 and 5 could have been filled by the iwlcore code.
		 * Let's clear them before pushing to the 3945.
		 */
		active_rxon->reserved4 = 0;
		active_rxon->reserved5 = 0;
		rc = il_send_cmd_pdu(il, C_RXON, sizeof(struct il3945_rxon_cmd),
				     &il->active);

		/* If the mask clearing failed then we set
		 * active_rxon back to what it was previously */
		if (rc) {
			active_rxon->filter_flags |= RXON_FILTER_ASSOC_MSK;
			IL_ERR("Error clearing ASSOC_MSK on current "
			       "configuration (%d).\n", rc);
			return rc;
		}
		il_clear_ucode_stations(il);
		il_restore_stations(il);
	}

	D_INFO("Sending RXON\n" "* with%s RXON_FILTER_ASSOC_MSK\n"
	       "* channel = %d\n" "* bssid = %pM\n", (new_assoc ? "" : "out"),
	       le16_to_cpu(staging_rxon->channel), staging_rxon->bssid_addr);

	/*
	 * reserved4 and 5 could have been filled by the iwlcore code.
	 * Let's clear them before pushing to the 3945.
	 */
	staging_rxon->reserved4 = 0;
	staging_rxon->reserved5 = 0;

	il_set_rxon_hwcrypto(il, !il3945_mod_params.sw_crypto);

	/* Apply the new configuration */
	rc = il_send_cmd_pdu(il, C_RXON, sizeof(struct il3945_rxon_cmd),
			     staging_rxon);
	if (rc) {
		IL_ERR("Error setting new configuration (%d).\n", rc);
		return rc;
	}

	memcpy(active_rxon, staging_rxon, sizeof(*active_rxon));

	if (!new_assoc) {
		il_clear_ucode_stations(il);
		il_restore_stations(il);
	}

	/* If we issue a new RXON command which required a tune then we must
	 * send a new TXPOWER command or we won't be able to Tx any frames */
	rc = il_set_tx_power(il, il->tx_power_next, true);
	if (rc) {
		IL_ERR("Error setting Tx power (%d).\n", rc);
		return rc;
	}

	/* Init the hardware's rate fallback order based on the band */
	rc = il3945_init_hw_rate_table(il);
	if (rc) {
		IL_ERR("Error setting HW rate table: %02X\n", rc);
		return -EIO;
	}

	return 0;
}