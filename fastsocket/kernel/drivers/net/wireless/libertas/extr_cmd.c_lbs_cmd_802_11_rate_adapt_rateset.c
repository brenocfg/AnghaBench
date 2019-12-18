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
struct lbs_private {int enablehwauto; void* ratebitmap; int /*<<< orphan*/  cur_rate; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_rate_adapt_rateset {void* enablehwauto; void* bitmap; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_RATE_ADAPT_RATESET ; 
 int CMD_ACT_GET ; 
 int EINVAL ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_rate_adapt_rateset*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 void* lbs_rate_to_fw_bitmap (int /*<<< orphan*/ ,int) ; 
 void* le16_to_cpu (void*) ; 

int lbs_cmd_802_11_rate_adapt_rateset(struct lbs_private *priv,
				      uint16_t cmd_action)
{
	struct cmd_ds_802_11_rate_adapt_rateset cmd;
	int ret;

	lbs_deb_enter(LBS_DEB_CMD);

	if (!priv->cur_rate && !priv->enablehwauto)
		return -EINVAL;

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));

	cmd.action = cpu_to_le16(cmd_action);
	cmd.enablehwauto = cpu_to_le16(priv->enablehwauto);
	cmd.bitmap = lbs_rate_to_fw_bitmap(priv->cur_rate, priv->enablehwauto);
	ret = lbs_cmd_with_response(priv, CMD_802_11_RATE_ADAPT_RATESET, &cmd);
	if (!ret && cmd_action == CMD_ACT_GET) {
		priv->ratebitmap = le16_to_cpu(cmd.bitmap);
		priv->enablehwauto = le16_to_cpu(cmd.enablehwauto);
	}

	lbs_deb_leave_args(LBS_DEB_CMD, "ret %d", ret);
	return ret;
}