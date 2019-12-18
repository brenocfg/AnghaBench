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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct cmtp_session {int num; } ;
struct cmtp_application {scalar_t__ state; int /*<<< orphan*/  mapping; } ;
struct capi_ctr {struct cmtp_session* driverdata; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct capi_ctr*,struct sk_buff*) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_APPID (int /*<<< orphan*/ ) ; 
 int CAPIMSG_CONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_SETAPPID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAPIMSG_SETCONTROL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CAPI_ILLAPPNR ; 
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CMTP_APPLID ; 
 struct cmtp_application* cmtp_application_get (struct cmtp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmtp_send_capimsg (struct cmtp_session*,struct sk_buff*) ; 

__attribute__((used)) static u16 cmtp_send_message(struct capi_ctr *ctrl, struct sk_buff *skb)
{
	struct cmtp_session *session = ctrl->driverdata;
	struct cmtp_application *application;
	__u16 appl;
	__u32 contr;

	BT_DBG("ctrl %p skb %p", ctrl, skb);

	appl = CAPIMSG_APPID(skb->data);
	contr = CAPIMSG_CONTROL(skb->data);

	application = cmtp_application_get(session, CMTP_APPLID, appl);
	if ((!application) || (application->state != BT_CONNECTED)) {
		BT_ERR("Can't find application with id %d", appl);
		return CAPI_ILLAPPNR;
	}

	CAPIMSG_SETAPPID(skb->data, application->mapping);

	if ((contr & 0x7f) == session->num) {
		contr = (contr & 0xffffff80) | 0x01;
		CAPIMSG_SETCONTROL(skb->data, contr);
	}

	cmtp_send_capimsg(session, skb);

	return CAPI_NOERROR;
}