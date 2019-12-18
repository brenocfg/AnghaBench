#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int prim_version_no; int param_count; int prot_version; scalar_t__ ipa_enabled; scalar_t__ ipa_supported; void* rel_adapter_no; int /*<<< orphan*/  adapter_type; int /*<<< orphan*/  seqno; int /*<<< orphan*/  initiator; void* command; } ;
struct qeth_ipa_cmd {TYPE_4__ hdr; } ;
struct TYPE_7__ {scalar_t__ layer2; } ;
struct TYPE_6__ {scalar_t__ portno; int /*<<< orphan*/  link_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  ipa; } ;
struct qeth_card {TYPE_3__ options; TYPE_2__ info; TYPE_1__ seqno; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  void* __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_CMD_INITIATOR_HOST ; 
 int /*<<< orphan*/  memset (struct qeth_ipa_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qeth_get_ipa_adp_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_fill_ipacmd_header(struct qeth_card *card,
		struct qeth_ipa_cmd *cmd, __u8 command,
		enum qeth_prot_versions prot)
{
	memset(cmd, 0, sizeof(struct qeth_ipa_cmd));
	cmd->hdr.command = command;
	cmd->hdr.initiator = IPA_CMD_INITIATOR_HOST;
	cmd->hdr.seqno = card->seqno.ipa;
	cmd->hdr.adapter_type = qeth_get_ipa_adp_type(card->info.link_type);
	cmd->hdr.rel_adapter_no = (__u8) card->info.portno;
	if (card->options.layer2)
		cmd->hdr.prim_version_no = 2;
	else
		cmd->hdr.prim_version_no = 1;
	cmd->hdr.param_count = 1;
	cmd->hdr.prot_version = prot;
	cmd->hdr.ipa_supported = 0;
	cmd->hdr.ipa_enabled = 0;
}