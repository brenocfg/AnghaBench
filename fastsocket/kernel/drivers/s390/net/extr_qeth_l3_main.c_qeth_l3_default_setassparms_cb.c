#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  flags_32bit; } ;
struct TYPE_14__ {scalar_t__ return_code; scalar_t__ assist_no; scalar_t__ command_code; } ;
struct TYPE_16__ {TYPE_6__ data; TYPE_5__ hdr; } ;
struct TYPE_17__ {TYPE_7__ setassparms; } ;
struct TYPE_13__ {scalar_t__ return_code; scalar_t__ prot_version; int /*<<< orphan*/  ipa_enabled; } ;
struct qeth_ipa_cmd {TYPE_8__ data; TYPE_4__ hdr; } ;
struct TYPE_18__ {int /*<<< orphan*/  tx_csum_mask; int /*<<< orphan*/  csum_mask; } ;
struct TYPE_11__ {int /*<<< orphan*/  enabled_funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  enabled_funcs; } ;
struct TYPE_12__ {TYPE_2__ ipa6; TYPE_1__ ipa4; } ;
struct qeth_card {TYPE_9__ info; TYPE_3__ options; } ;

/* Variables and functions */
 scalar_t__ IPA_CMD_ASS_START ; 
 scalar_t__ IPA_INBOUND_CHECKSUM ; 
 scalar_t__ IPA_OUTBOUND_CHECKSUM ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 scalar_t__ QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  TRACE ; 

__attribute__((used)) static int qeth_l3_default_setassparms_cb(struct qeth_card *card,
			struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 4, "defadpcb");

	cmd = (struct qeth_ipa_cmd *) data;
	if (cmd->hdr.return_code == 0) {
		cmd->hdr.return_code = cmd->data.setassparms.hdr.return_code;
		if (cmd->hdr.prot_version == QETH_PROT_IPV4)
			card->options.ipa4.enabled_funcs = cmd->hdr.ipa_enabled;
		if (cmd->hdr.prot_version == QETH_PROT_IPV6)
			card->options.ipa6.enabled_funcs = cmd->hdr.ipa_enabled;
	}
	if (cmd->data.setassparms.hdr.assist_no == IPA_INBOUND_CHECKSUM &&
	    cmd->data.setassparms.hdr.command_code == IPA_CMD_ASS_START) {
		card->info.csum_mask = cmd->data.setassparms.data.flags_32bit;
		QETH_DBF_TEXT_(TRACE, 3, "csum:%d", card->info.csum_mask);
	}
	if (cmd->data.setassparms.hdr.assist_no == IPA_OUTBOUND_CHECKSUM &&
	    cmd->data.setassparms.hdr.command_code == IPA_CMD_ASS_START) {
		card->info.tx_csum_mask =
			cmd->data.setassparms.data.flags_32bit;
		QETH_DBF_TEXT_(TRACE, 3, "tcsu:%d", card->info.tx_csum_mask);
	}

	return 0;
}