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
typedef  int /*<<< orphan*/  u8 ;
struct lbs_private {int seqnum; int (* hw_host_to_card ) (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct cmd_header {scalar_t__ result; void* seqnum; void* size; void* command; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CMD_802_11_WAKEUP_CONFIRM ; 
 int /*<<< orphan*/  LBS_DEB_HOST ; 
 int /*<<< orphan*/  MVMS_CMD ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_pr_alert (char*) ; 
 int stub1 (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lbs_send_confirmwake(struct lbs_private *priv)
{
	struct cmd_header cmd;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_HOST);

	cmd.command = cpu_to_le16(CMD_802_11_WAKEUP_CONFIRM);
	cmd.size = cpu_to_le16(sizeof(cmd));
	cmd.seqnum = cpu_to_le16(++priv->seqnum);
	cmd.result = 0;

	lbs_deb_hex(LBS_DEB_HOST, "wake confirm", (u8 *) &cmd,
		sizeof(cmd));

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) &cmd, sizeof(cmd));
	if (ret)
		lbs_pr_alert("SEND_WAKEC_CMD: Host to Card failed for Confirm Wake\n");

	lbs_deb_leave_args(LBS_DEB_HOST, "ret %d", ret);
	return ret;
}