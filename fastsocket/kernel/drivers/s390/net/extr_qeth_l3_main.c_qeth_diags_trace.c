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
struct TYPE_3__ {int subcmd_len; int action; int /*<<< orphan*/  type; int /*<<< orphan*/  subcmd; } ;
struct TYPE_4__ {TYPE_1__ diagass; } ;
struct qeth_ipa_cmd {TYPE_2__ data; } ;
struct qeth_cmd_buffer {scalar_t__ data; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_diags_trace_cmds { ____Placeholder_qeth_diags_trace_cmds } qeth_diags_trace_cmds ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_CMD_SET_DIAG_ASS ; 
 scalar_t__ IPA_PDU_HEADER_SIZE ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DIAGS_CMD_TRACE ; 
 int /*<<< orphan*/  QETH_DIAGS_TYPE_HIPERSOCKET ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  qeth_diags_trace_cb ; 
 struct qeth_cmd_buffer* qeth_get_ipacmd_buffer (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qeth_diags_trace(struct qeth_card *card, enum qeth_diags_trace_cmds diags_cmd)
{
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd    *cmd;

	QETH_DBF_TEXT(SETUP, 2, "diagtrac");

	iob = qeth_get_ipacmd_buffer(card, IPA_CMD_SET_DIAG_ASS, 0);
	cmd = (struct qeth_ipa_cmd *)(iob->data+IPA_PDU_HEADER_SIZE);
	cmd->data.diagass.subcmd_len = 16;
	cmd->data.diagass.subcmd = QETH_DIAGS_CMD_TRACE;
	cmd->data.diagass.type = QETH_DIAGS_TYPE_HIPERSOCKET;
	cmd->data.diagass.action = diags_cmd;
	return qeth_send_ipa_cmd(card, iob, qeth_diags_trace_cb, NULL);
}