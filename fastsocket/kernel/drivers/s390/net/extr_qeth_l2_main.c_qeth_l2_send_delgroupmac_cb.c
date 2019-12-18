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
struct TYPE_6__ {scalar_t__ return_code; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mac; } ;
struct TYPE_5__ {TYPE_1__ setdelmac; } ;
struct qeth_ipa_cmd {TYPE_3__ hdr; TYPE_2__ data; } ;
struct qeth_card {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 

__attribute__((used)) static int qeth_l2_send_delgroupmac_cb(struct qeth_card *card,
				struct qeth_reply *reply,
				unsigned long data)
{
	struct qeth_ipa_cmd *cmd;
	__u8 *mac;

	QETH_DBF_TEXT(TRACE, 2, "L2Dgmacb");
	cmd = (struct qeth_ipa_cmd *) data;
	mac = &cmd->data.setdelmac.mac[0];
	if (cmd->hdr.return_code)
		QETH_DBF_MESSAGE(2, "Could not delete group MAC %pM on %s: %x\n",
			  mac, QETH_CARD_IFNAME(card), cmd->hdr.return_code);
	return 0;
}