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
struct ipw_wep_key {int key_index; scalar_t__ key_size; int /*<<< orphan*/  key; scalar_t__ seq_num; int /*<<< orphan*/  cmd_id; } ;
struct ipw_priv {TYPE_2__* ieee; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * keys; scalar_t__* key_sizes; } ;
struct TYPE_4__ {TYPE_1__ sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DINO_CMD_WEP_KEY ; 
 int /*<<< orphan*/  IPW_CMD_WEP_KEY ; 
 int /*<<< orphan*/  ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,struct ipw_wep_key*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ipw_send_wep_keys(struct ipw_priv *priv, int type)
{
	struct ipw_wep_key key;
	int i;

	key.cmd_id = DINO_CMD_WEP_KEY;
	key.seq_num = 0;

	/* Note: AES keys cannot be set for multiple times.
	 * Only set it at the first time. */
	for (i = 0; i < 4; i++) {
		key.key_index = i | type;
		if (!(priv->ieee->sec.flags & (1 << i))) {
			key.key_size = 0;
			continue;
		}

		key.key_size = priv->ieee->sec.key_sizes[i];
		memcpy(key.key, priv->ieee->sec.keys[i], key.key_size);

		ipw_send_cmd_pdu(priv, IPW_CMD_WEP_KEY, sizeof(key), &key);
	}
}