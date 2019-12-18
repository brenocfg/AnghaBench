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
typedef  int uint16_t ;
struct lbs_private {int wep_tx_keyidx; } ;
struct enc_key {int len; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {void* size; void* command; } ;
struct cmd_ds_802_11_set_wep {void* keyindex; int /*<<< orphan*/ * keymaterial; int /*<<< orphan*/ * keytype; void* action; TYPE_1__ hdr; } ;
struct assoc_request {int wep_tx_keyidx; struct enc_key* wep_keys; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CMD_802_11_SET_WEP ; 
 int CMD_ACT_ADD ; 
 int CMD_ACT_REMOVE ; 
 int /*<<< orphan*/  CMD_TYPE_WEP_104_BIT ; 
 int /*<<< orphan*/  CMD_TYPE_WEP_40_BIT ; 
 int CMD_WEP_KEY_INDEX_MASK ; 
#define  KEY_LEN_WEP_104 129 
#define  KEY_LEN_WEP_40 128 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int,struct cmd_ds_802_11_set_wep*) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,int,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_set_wep*,int /*<<< orphan*/ ,int) ; 

int lbs_cmd_802_11_set_wep(struct lbs_private *priv, uint16_t cmd_action,
			   struct assoc_request *assoc)
{
	struct cmd_ds_802_11_set_wep cmd;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_CMD);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.command = cpu_to_le16(CMD_802_11_SET_WEP);
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));

	cmd.action = cpu_to_le16(cmd_action);

	if (cmd_action == CMD_ACT_ADD) {
		int i;

		/* default tx key index */
		cmd.keyindex = cpu_to_le16(assoc->wep_tx_keyidx &
					   CMD_WEP_KEY_INDEX_MASK);

		/* Copy key types and material to host command structure */
		for (i = 0; i < 4; i++) {
			struct enc_key *pkey = &assoc->wep_keys[i];

			switch (pkey->len) {
			case KEY_LEN_WEP_40:
				cmd.keytype[i] = CMD_TYPE_WEP_40_BIT;
				memmove(cmd.keymaterial[i], pkey->key, pkey->len);
				lbs_deb_cmd("SET_WEP: add key %d (40 bit)\n", i);
				break;
			case KEY_LEN_WEP_104:
				cmd.keytype[i] = CMD_TYPE_WEP_104_BIT;
				memmove(cmd.keymaterial[i], pkey->key, pkey->len);
				lbs_deb_cmd("SET_WEP: add key %d (104 bit)\n", i);
				break;
			case 0:
				break;
			default:
				lbs_deb_cmd("SET_WEP: invalid key %d, length %d\n",
					    i, pkey->len);
				ret = -1;
				goto done;
				break;
			}
		}
	} else if (cmd_action == CMD_ACT_REMOVE) {
		/* ACT_REMOVE clears _all_ WEP keys */

		/* default tx key index */
		cmd.keyindex = cpu_to_le16(priv->wep_tx_keyidx &
					   CMD_WEP_KEY_INDEX_MASK);
		lbs_deb_cmd("SET_WEP: remove key %d\n", priv->wep_tx_keyidx);
	}

	ret = lbs_cmd_with_response(priv, CMD_802_11_SET_WEP, &cmd);
done:
	lbs_deb_leave_args(LBS_DEB_CMD, "ret %d", ret);
	return ret;
}