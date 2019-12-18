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
struct lcs_cmd {scalar_t__ initiator; int cmd_code; } ;
struct lcs_card {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  LCS_CMD_STARTLAN 130 
#define  LCS_CMD_STARTUP 129 
#define  LCS_CMD_STOPLAN 128 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LCS_INITIATOR_LGW ; 
 int /*<<< orphan*/  lcs_notify_lancmd_waiters (struct lcs_card*,struct lcs_cmd*) ; 
 int /*<<< orphan*/  lcs_schedule_recovery (struct lcs_card*) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
lcs_get_control(struct lcs_card *card, struct lcs_cmd *cmd)
{
	LCS_DBF_TEXT(5, trace, "getctrl");
	if (cmd->initiator == LCS_INITIATOR_LGW) {
		switch(cmd->cmd_code) {
		case LCS_CMD_STARTUP:
		case LCS_CMD_STARTLAN:
			lcs_schedule_recovery(card);
			break;
		case LCS_CMD_STOPLAN:
			pr_warning("Stoplan for %s initiated by LGW.\n",
				   card->dev->name);
			if (card->dev)
				netif_carrier_off(card->dev);
			break;
		default:
			LCS_DBF_TEXT(5, trace, "noLGWcmd");
			break;
		}
	} else
		lcs_notify_lancmd_waiters(card, cmd);
}