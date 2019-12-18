#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qmi_msg {int txn_id; int type; unsigned char* tlv; scalar_t__ size; int /*<<< orphan*/  client_id; int /*<<< orphan*/  service; } ;
struct qmi_ctxt {int wds_txn_id; int /*<<< orphan*/  wds_handle; int /*<<< orphan*/  wds_client_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMI_WDS ; 
 int QMUX_HEADER ; 
 int /*<<< orphan*/  QMUX_OVERHEAD ; 
 int /*<<< orphan*/  qmi_add_tlv (struct qmi_msg*,int,int,int /*<<< orphan*/ *) ; 
 int qmi_send (struct qmi_ctxt*,struct qmi_msg*) ; 

__attribute__((used)) static int qmi_network_down(struct qmi_ctxt *ctxt)
{
	unsigned char data[16 + QMUX_OVERHEAD];
	struct qmi_msg msg;

	msg.service = QMI_WDS;
	msg.client_id = ctxt->wds_client_id;
	msg.txn_id = ctxt->wds_txn_id;
	msg.type = 0x0021;
	msg.size = 0;
	msg.tlv = data + QMUX_HEADER;

	ctxt->wds_txn_id += 2;

	qmi_add_tlv(&msg, 0x01, sizeof(ctxt->wds_handle), &ctxt->wds_handle);

	return qmi_send(ctxt, &msg);
}