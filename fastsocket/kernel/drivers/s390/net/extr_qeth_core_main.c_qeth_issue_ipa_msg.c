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
struct TYPE_3__ {int command; } ;
struct qeth_ipa_cmd {TYPE_1__ hdr; } ;
struct qeth_card {TYPE_2__* gdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 char* qeth_get_ipa_cmd_name (int) ; 
 int /*<<< orphan*/  qeth_get_ipa_msg (int) ; 

__attribute__((used)) static void qeth_issue_ipa_msg(struct qeth_ipa_cmd *cmd, int rc,
		struct qeth_card *card)
{
	char *ipa_name;
	int com = cmd->hdr.command;
	ipa_name = qeth_get_ipa_cmd_name(com);
	if (rc)
		QETH_DBF_MESSAGE(2, "IPA: %s(x%X) for %s/%s returned "
				"x%X \"%s\"\n",
				ipa_name, com, dev_name(&card->gdev->dev),
				QETH_CARD_IFNAME(card), rc,
				qeth_get_ipa_msg(rc));
	else
		QETH_DBF_MESSAGE(5, "IPA: %s(x%X) for %s/%s succeeded\n",
				ipa_name, com, dev_name(&card->gdev->dev),
				QETH_CARD_IFNAME(card));
}