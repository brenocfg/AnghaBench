#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct qeth_set_access_ctrl {int subcmd_code; } ;
struct qeth_ipacmd_setadpparms_hdr {int dummy; } ;
struct TYPE_10__ {struct qeth_set_access_ctrl set_access_ctrl; } ;
struct TYPE_11__ {TYPE_4__ data; } ;
struct TYPE_12__ {TYPE_5__ setadapterparms; } ;
struct qeth_ipa_cmd {TYPE_6__ data; } ;
struct qeth_cmd_buffer {scalar_t__ data; } ;
struct qeth_card {TYPE_3__* gdev; } ;
typedef  enum qeth_ipa_isolation_modes { ____Placeholder_qeth_ipa_isolation_modes } qeth_ipa_isolation_modes ;
struct TYPE_7__ {int name; } ;
struct TYPE_8__ {TYPE_1__ kobj; } ;
struct TYPE_9__ {TYPE_2__ dev; } ;

/* Variables and functions */
 scalar_t__ IPA_PDU_HEADER_SIZE ; 
 int /*<<< orphan*/  IPA_SETADP_SET_ACCESS_CONTROL ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  TRACE ; 
 struct qeth_cmd_buffer* qeth_get_adapter_cmd (struct qeth_card*,int /*<<< orphan*/ ,int) ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qeth_setadpparms_set_access_ctrl_cb ; 

__attribute__((used)) static int qeth_setadpparms_set_access_ctrl(struct qeth_card *card,
		enum qeth_ipa_isolation_modes isolation, int fallback)
{
	int rc;
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;
	struct qeth_set_access_ctrl *access_ctrl_req;

	QETH_DBF_TEXT(TRACE, 4, "setacctl");

	QETH_DBF_TEXT_(SETUP, 2, "setacctl");
	QETH_DBF_TEXT_(SETUP, 2, "%s", card->gdev->dev.kobj.name);

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_SET_ACCESS_CONTROL,
				   sizeof(struct qeth_ipacmd_setadpparms_hdr) +
				   sizeof(struct qeth_set_access_ctrl));
	cmd = (struct qeth_ipa_cmd *)(iob->data+IPA_PDU_HEADER_SIZE);
	access_ctrl_req = &cmd->data.setadapterparms.data.set_access_ctrl;
	access_ctrl_req->subcmd_code = isolation;

	rc = qeth_send_ipa_cmd(card, iob, qeth_setadpparms_set_access_ctrl_cb,
			       &fallback);
	QETH_DBF_TEXT_(SETUP, 2, "rc=%d", rc);
	return rc;
}