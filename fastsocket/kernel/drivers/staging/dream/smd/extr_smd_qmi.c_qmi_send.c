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
struct qmi_msg {unsigned int size; int txn_id; int type; int /*<<< orphan*/  tlv; int /*<<< orphan*/  service; int /*<<< orphan*/  client_id; } ;
struct qmi_ctxt {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMI_CTL ; 
 int QMUX_HEADER ; 
 int /*<<< orphan*/  qmi_dump_msg (struct qmi_msg*,char*) ; 
 int smd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int qmi_send(struct qmi_ctxt *ctxt, struct qmi_msg *msg)
{
	unsigned char *data;
	unsigned hlen;
	unsigned len;
	int r;

	qmi_dump_msg(msg, "send");

	if (msg->service == QMI_CTL) {
		hlen = QMUX_HEADER - 1;
	} else {
		hlen = QMUX_HEADER;
	}

	/* QMUX length is total header + total payload - IFC selector */
	len = hlen + msg->size - 1;
	if (len > 0xffff)
		return -1;

	data = msg->tlv - hlen;

	/* prepend encap and qmux header */
	*data++ = 0x01; /* ifc selector */

	/* qmux header */
	*data++ = len;
	*data++ = len >> 8;
	*data++ = 0x00; /* flags: client */
	*data++ = msg->service;
	*data++ = msg->client_id;

	/* qmi header */
	*data++ = 0x00; /* flags: send */
	*data++ = msg->txn_id;
	if (msg->service != QMI_CTL)
		*data++ = msg->txn_id >> 8;

	*data++ = msg->type;
	*data++ = msg->type >> 8;
	*data++ = msg->size;
	*data++ = msg->size >> 8;

	/* len + 1 takes the interface selector into account */
	r = smd_write(ctxt->ch, msg->tlv - hlen, len + 1);

	if (r != len) {
		return -1;
	} else {
		return 0;
	}
}