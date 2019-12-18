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
struct lbs_private {int wol_criteria; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_HOST_SLEEP_ACTIVATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  LBS_DEB_FW ; 
 int __lbs_cmd (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,...) ; 
 int /*<<< orphan*/  lbs_suspend_callback ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 

int lbs_suspend(struct lbs_private *priv)
{
	struct cmd_header cmd;
	int ret;

	lbs_deb_enter(LBS_DEB_FW);

	if (priv->wol_criteria == 0xffffffff) {
		lbs_pr_info("Suspend attempt without configuring wake params!\n");
		return -EINVAL;
	}

	memset(&cmd, 0, sizeof(cmd));

	ret = __lbs_cmd(priv, CMD_802_11_HOST_SLEEP_ACTIVATE, &cmd,
			sizeof(cmd), lbs_suspend_callback, 0);
	if (ret)
		lbs_pr_info("HOST_SLEEP_ACTIVATE failed: %d\n", ret);

	lbs_deb_leave_args(LBS_DEB_FW, "ret %d", ret);
	return ret;
}