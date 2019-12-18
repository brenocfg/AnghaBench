#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  key_mapping_keys; } ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_3__* stations; int /*<<< orphan*/  ucode_key_table; TYPE_1__ _4965; int /*<<< orphan*/  mutex; } ;
struct il_hw_key {int dummy; } ;
struct il_addsta_cmd {int dummy; } ;
struct il4965_keyinfo {int dummy; } ;
struct ieee80211_key_conf {size_t keyidx; int /*<<< orphan*/  hw_key_idx; } ;
struct TYPE_7__ {int /*<<< orphan*/  modify_mask; } ;
struct TYPE_9__ {int key_flags; int /*<<< orphan*/  key_offset; } ;
struct TYPE_10__ {int /*<<< orphan*/  mode; TYPE_2__ sta; TYPE_4__ key; } ;
struct TYPE_8__ {TYPE_5__ sta; TYPE_4__ keyinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  D_WEP (char*,...) ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_WARN (char*,size_t,int) ; 
 int /*<<< orphan*/  STA_CONTROL_MODIFY_MSK ; 
 int STA_KEY_FLG_INVALID ; 
 int STA_KEY_FLG_KEYID_POS ; 
 int STA_KEY_FLG_NO_ENC ; 
 int /*<<< orphan*/  STA_MODIFY_KEY_MASK ; 
 scalar_t__ il_is_rfkill (struct il_priv*) ; 
 int il_send_add_sta (struct il_priv*,struct il_addsta_cmd*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct il_addsta_cmd*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
il4965_remove_dynamic_key(struct il_priv *il,
			  struct ieee80211_key_conf *keyconf, u8 sta_id)
{
	unsigned long flags;
	u16 key_flags;
	u8 keyidx;
	struct il_addsta_cmd sta_cmd;

	lockdep_assert_held(&il->mutex);

	il->_4965.key_mapping_keys--;

	spin_lock_irqsave(&il->sta_lock, flags);
	key_flags = le16_to_cpu(il->stations[sta_id].sta.key.key_flags);
	keyidx = (key_flags >> STA_KEY_FLG_KEYID_POS) & 0x3;

	D_WEP("Remove dynamic key: idx=%d sta=%d\n", keyconf->keyidx, sta_id);

	if (keyconf->keyidx != keyidx) {
		/* We need to remove a key with idx different that the one
		 * in the uCode. This means that the key we need to remove has
		 * been replaced by another one with different idx.
		 * Don't do anything and return ok
		 */
		spin_unlock_irqrestore(&il->sta_lock, flags);
		return 0;
	}

	if (il->stations[sta_id].sta.key.key_flags & STA_KEY_FLG_INVALID) {
		IL_WARN("Removing wrong key %d 0x%x\n", keyconf->keyidx,
			key_flags);
		spin_unlock_irqrestore(&il->sta_lock, flags);
		return 0;
	}

	if (!test_and_clear_bit
	    (il->stations[sta_id].sta.key.key_offset, &il->ucode_key_table))
		IL_ERR("idx %d not used in uCode key table.\n",
		       il->stations[sta_id].sta.key.key_offset);
	memset(&il->stations[sta_id].keyinfo, 0, sizeof(struct il_hw_key));
	memset(&il->stations[sta_id].sta.key, 0, sizeof(struct il4965_keyinfo));
	il->stations[sta_id].sta.key.key_flags =
	    STA_KEY_FLG_NO_ENC | STA_KEY_FLG_INVALID;
	il->stations[sta_id].sta.key.key_offset = keyconf->hw_key_idx;
	il->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;

	if (il_is_rfkill(il)) {
		D_WEP
		    ("Not sending C_ADD_STA command because RFKILL enabled.\n");
		spin_unlock_irqrestore(&il->sta_lock, flags);
		return 0;
	}
	memcpy(&sta_cmd, &il->stations[sta_id].sta,
	       sizeof(struct il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	return il_send_add_sta(il, &sta_cmd, CMD_SYNC);
}