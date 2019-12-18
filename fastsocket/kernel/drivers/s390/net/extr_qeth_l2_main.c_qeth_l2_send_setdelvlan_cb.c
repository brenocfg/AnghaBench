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
struct qeth_reply {int dummy; } ;
struct TYPE_4__ {scalar_t__ return_code; scalar_t__ command; } ;
struct TYPE_6__ {int /*<<< orphan*/  vlan_id; } ;
struct TYPE_5__ {TYPE_3__ setdelvlan; } ;
struct qeth_ipa_cmd {TYPE_1__ hdr; TYPE_2__ data; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 scalar_t__ CARD_BUS_ID (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE ; 

__attribute__((used)) static int qeth_l2_send_setdelvlan_cb(struct qeth_card *card,
			struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 2, "L2sdvcb");
	cmd = (struct qeth_ipa_cmd *) data;
	if (cmd->hdr.return_code) {
		QETH_DBF_MESSAGE(2, "Error in processing VLAN %i on %s: 0x%x. "
			  "Continuing\n", cmd->data.setdelvlan.vlan_id,
			  QETH_CARD_IFNAME(card), cmd->hdr.return_code);
		QETH_DBF_TEXT_(TRACE, 2, "L2VL%4x", cmd->hdr.command);
		QETH_DBF_TEXT_(TRACE, 2, "L2%s", CARD_BUS_ID(card));
		QETH_DBF_TEXT_(TRACE, 2, "err%d", cmd->hdr.return_code);
	}
	return 0;
}