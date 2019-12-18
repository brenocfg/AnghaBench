#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_2__ change_addr; } ;
struct TYPE_11__ {TYPE_3__ data; } ;
struct TYPE_12__ {TYPE_4__ setadapterparms; } ;
struct qeth_ipa_cmd {TYPE_5__ data; } ;
struct TYPE_14__ {int mac_bits; } ;
struct TYPE_13__ {int /*<<< orphan*/  layer2; } ;
struct qeth_card {TYPE_7__ info; TYPE_1__* dev; TYPE_6__ options; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSA_ADDR_LEN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int QETH_LAYER2_MAC_READ ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_default_setadapterparms_cb (struct qeth_card*,struct qeth_reply*,unsigned long) ; 

__attribute__((used)) static int qeth_setadpparms_change_macaddr_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 4, "chgmaccb");

	cmd = (struct qeth_ipa_cmd *) data;
	if (!card->options.layer2 ||
	    !(card->info.mac_bits & QETH_LAYER2_MAC_READ)) {
		memcpy(card->dev->dev_addr,
		       &cmd->data.setadapterparms.data.change_addr.addr,
		       OSA_ADDR_LEN);
		card->info.mac_bits |= QETH_LAYER2_MAC_READ;
	}
	qeth_default_setadapterparms_cb(card, reply, (unsigned long) cmd);
	return 0;
}