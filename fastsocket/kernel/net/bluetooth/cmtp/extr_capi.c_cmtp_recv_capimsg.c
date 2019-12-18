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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct capi_ctr {int dummy; } ;
struct cmtp_session {int flags; int num; struct capi_ctr ctrl; } ;
struct cmtp_application {int appl; } ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int CAPICMD (scalar_t__,int /*<<< orphan*/ ) ; 
 int CAPIMSG_APPID (int /*<<< orphan*/ ) ; 
 scalar_t__ CAPIMSG_COMMAND (int /*<<< orphan*/ ) ; 
 int CAPIMSG_CONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_SETAPPID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CAPIMSG_SETCONTROL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CAPIMSG_SUBCOMMAND (int /*<<< orphan*/ ) ; 
 scalar_t__ CAPI_INTEROPERABILITY ; 
 scalar_t__ CAPI_MSG_BASELEN ; 
 int CMTP_LOOPBACK ; 
 int /*<<< orphan*/  CMTP_MAPPING ; 
 int /*<<< orphan*/  capi_ctr_handle_message (struct capi_ctr*,int,struct sk_buff*) ; 
 struct cmtp_application* cmtp_application_get (struct cmtp_session*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmtp_recv_interopmsg (struct cmtp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

void cmtp_recv_capimsg(struct cmtp_session *session, struct sk_buff *skb)
{
	struct capi_ctr *ctrl = &session->ctrl;
	struct cmtp_application *application;
	__u16 cmd, appl;
	__u32 contr;

	BT_DBG("session %p skb %p len %d", session, skb, skb->len);

	if (skb->len < CAPI_MSG_BASELEN)
		return;

	if (CAPIMSG_COMMAND(skb->data) == CAPI_INTEROPERABILITY) {
		cmtp_recv_interopmsg(session, skb);
		return;
	}

	if (session->flags & (1 << CMTP_LOOPBACK)) {
		kfree_skb(skb);
		return;
	}

	cmd = CAPICMD(CAPIMSG_COMMAND(skb->data), CAPIMSG_SUBCOMMAND(skb->data));
	appl = CAPIMSG_APPID(skb->data);
	contr = CAPIMSG_CONTROL(skb->data);

	application = cmtp_application_get(session, CMTP_MAPPING, appl);
	if (application) {
		appl = application->appl;
		CAPIMSG_SETAPPID(skb->data, appl);
	} else {
		BT_ERR("Can't find application with id %d", appl);
		kfree_skb(skb);
		return;
	}

	if ((contr & 0x7f) == 0x01) {
		contr = (contr & 0xffffff80) | session->num;
		CAPIMSG_SETCONTROL(skb->data, contr);
	}

	if (!ctrl) {
		BT_ERR("Can't find controller %d for message", session->num);
		kfree_skb(skb);
		return;
	}

	capi_ctr_handle_message(ctrl, appl, skb);
}