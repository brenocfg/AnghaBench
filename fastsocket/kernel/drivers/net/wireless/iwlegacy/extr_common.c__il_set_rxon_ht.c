#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct il_rxon_cmd {int flags; } ;
struct TYPE_4__ {int protection; int /*<<< orphan*/  extension_chan_offset; int /*<<< orphan*/  enabled; } ;
struct il_priv {TYPE_2__ ht; TYPE_1__* ops; struct il_rxon_cmd staging; } ;
struct il_ht_config {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSOC (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int IEEE80211_HT_OP_MODE_PROTECTION_20MHZ ; 
#define  IEEE80211_HT_PARAM_CHA_SEC_ABOVE 130 
#define  IEEE80211_HT_PARAM_CHA_SEC_BELOW 129 
#define  IEEE80211_HT_PARAM_CHA_SEC_NONE 128 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int RXON_FLG_CHANNEL_MODE_LEGACY ; 
 int RXON_FLG_CHANNEL_MODE_MIXED ; 
 int RXON_FLG_CHANNEL_MODE_MSK ; 
 int RXON_FLG_CHANNEL_MODE_PURE_40 ; 
 int RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK ; 
 int RXON_FLG_HT40_PROT_MSK ; 
 int RXON_FLG_HT_OPERATING_MODE_POS ; 
 int RXON_FLG_HT_PROT_MSK ; 
 int cpu_to_le32 (int) ; 
 scalar_t__ il_is_ht40_tx_allowed (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 

__attribute__((used)) static void
_il_set_rxon_ht(struct il_priv *il, struct il_ht_config *ht_conf)
{
	struct il_rxon_cmd *rxon = &il->staging;

	if (!il->ht.enabled) {
		rxon->flags &=
		    ~(RXON_FLG_CHANNEL_MODE_MSK |
		      RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK | RXON_FLG_HT40_PROT_MSK
		      | RXON_FLG_HT_PROT_MSK);
		return;
	}

	rxon->flags |=
	    cpu_to_le32(il->ht.protection << RXON_FLG_HT_OPERATING_MODE_POS);

	/* Set up channel bandwidth:
	 * 20 MHz only, 20/40 mixed or pure 40 if ht40 ok */
	/* clear the HT channel mode before set the mode */
	rxon->flags &=
	    ~(RXON_FLG_CHANNEL_MODE_MSK | RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
	if (il_is_ht40_tx_allowed(il, NULL)) {
		/* pure ht40 */
		if (il->ht.protection == IEEE80211_HT_OP_MODE_PROTECTION_20MHZ) {
			rxon->flags |= RXON_FLG_CHANNEL_MODE_PURE_40;
			/* Note: control channel is opposite of extension channel */
			switch (il->ht.extension_chan_offset) {
			case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
				    ~RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				break;
			case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |= RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				break;
			}
		} else {
			/* Note: control channel is opposite of extension channel */
			switch (il->ht.extension_chan_offset) {
			case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
				    ~(RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				break;
			case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |= RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				break;
			case IEEE80211_HT_PARAM_CHA_SEC_NONE:
			default:
				/* channel location only valid if in Mixed mode */
				IL_ERR("invalid extension channel offset\n");
				break;
			}
		}
	} else {
		rxon->flags |= RXON_FLG_CHANNEL_MODE_LEGACY;
	}

	if (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	D_ASSOC("rxon flags 0x%X operation mode :0x%X "
		"extension channel offset 0x%x\n", le32_to_cpu(rxon->flags),
		il->ht.protection, il->ht.extension_chan_offset);
}