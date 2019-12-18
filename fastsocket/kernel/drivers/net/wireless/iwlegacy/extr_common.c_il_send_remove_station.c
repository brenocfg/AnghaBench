#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int status; } ;
struct TYPE_6__ {TYPE_2__ rem_sta; } ;
struct TYPE_4__ {int flags; } ;
struct il_rx_pkt {TYPE_3__ u; TYPE_1__ hdr; } ;
struct il_rem_sta_cmd {int num_sta; int /*<<< orphan*/  addr; } ;
struct il_priv {int /*<<< orphan*/  sta_lock; } ;
struct il_host_cmd {int len; scalar_t__ reply_page; int /*<<< orphan*/  flags; struct il_rem_sta_cmd* data; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  rm_sta_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int /*<<< orphan*/  C_REM_STA ; 
 int /*<<< orphan*/  D_ASSOC (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IL_CMD_FAILED_MSK ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
#define  REM_STA_SUCCESS_MSK 128 
 int /*<<< orphan*/  il_free_pages (struct il_priv*,scalar_t__) ; 
 int il_send_cmd (struct il_priv*,struct il_host_cmd*) ; 
 int /*<<< orphan*/  il_sta_ucode_deactivate (struct il_priv*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct il_rem_sta_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
il_send_remove_station(struct il_priv *il, const u8 * addr, int sta_id,
		       bool temporary)
{
	struct il_rx_pkt *pkt;
	int ret;

	unsigned long flags_spin;
	struct il_rem_sta_cmd rm_sta_cmd;

	struct il_host_cmd cmd = {
		.id = C_REM_STA,
		.len = sizeof(struct il_rem_sta_cmd),
		.flags = CMD_SYNC,
		.data = &rm_sta_cmd,
	};

	memset(&rm_sta_cmd, 0, sizeof(rm_sta_cmd));
	rm_sta_cmd.num_sta = 1;
	memcpy(&rm_sta_cmd.addr, addr, ETH_ALEN);

	cmd.flags |= CMD_WANT_SKB;

	ret = il_send_cmd(il, &cmd);

	if (ret)
		return ret;

	pkt = (struct il_rx_pkt *)cmd.reply_page;
	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from C_REM_STA (0x%08X)\n", pkt->hdr.flags);
		ret = -EIO;
	}

	if (!ret) {
		switch (pkt->u.rem_sta.status) {
		case REM_STA_SUCCESS_MSK:
			if (!temporary) {
				spin_lock_irqsave(&il->sta_lock, flags_spin);
				il_sta_ucode_deactivate(il, sta_id);
				spin_unlock_irqrestore(&il->sta_lock,
						       flags_spin);
			}
			D_ASSOC("C_REM_STA PASSED\n");
			break;
		default:
			ret = -EIO;
			IL_ERR("C_REM_STA failed\n");
			break;
		}
	}
	il_free_pages(il, cmd.reply_page);

	return ret;
}