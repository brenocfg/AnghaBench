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
struct TYPE_4__ {int assist_no; scalar_t__ seq_no; scalar_t__ return_code; void* command_code; void* length; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct TYPE_6__ {TYPE_2__ setassparms; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_cmd_buffer {scalar_t__ data; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  enum qeth_ipa_funcs { ____Placeholder_qeth_ipa_funcs } qeth_ipa_funcs ;
typedef  void* __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_CMD_SETASSPARMS ; 
 scalar_t__ IPA_PDU_HEADER_SIZE ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 struct qeth_cmd_buffer* qeth_get_ipacmd_buffer (struct qeth_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct qeth_cmd_buffer *qeth_l3_get_setassparms_cmd(
	struct qeth_card *card, enum qeth_ipa_funcs ipa_func, __u16 cmd_code,
	__u16 len, enum qeth_prot_versions prot)
{
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 4, "getasscm");
	iob = qeth_get_ipacmd_buffer(card, IPA_CMD_SETASSPARMS, prot);

	cmd = (struct qeth_ipa_cmd *)(iob->data+IPA_PDU_HEADER_SIZE);
	cmd->data.setassparms.hdr.assist_no = ipa_func;
	cmd->data.setassparms.hdr.length = 8 + len;
	cmd->data.setassparms.hdr.command_code = cmd_code;
	cmd->data.setassparms.hdr.return_code = 0;
	cmd->data.setassparms.hdr.seq_no = 0;

	return iob;
}