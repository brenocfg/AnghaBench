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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hidp_session {int /*<<< orphan*/  hid; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,struct sk_buff*,int /*<<< orphan*/ ,unsigned char) ; 
#define  HIDP_DATA_RTYPE_FEATURE 131 
#define  HIDP_DATA_RTYPE_INPUT 130 
#define  HIDP_DATA_RTYPE_OTHER 129 
#define  HIDP_DATA_RTYPE_OUPUT 128 
 int HIDP_HSHK_ERR_INVALID_PARAMETER ; 
 int HIDP_TRANS_HANDSHAKE ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  __hidp_send_ctrl_message (struct hidp_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_input_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_input_report (struct hidp_session*,struct sk_buff*) ; 
 int /*<<< orphan*/  hidp_set_timer (struct hidp_session*) ; 

__attribute__((used)) static void hidp_process_data(struct hidp_session *session, struct sk_buff *skb,
				unsigned char param)
{
	BT_DBG("session %p skb %p len %d param 0x%02x", session, skb, skb->len, param);

	switch (param) {
	case HIDP_DATA_RTYPE_INPUT:
		hidp_set_timer(session);

		if (session->input)
			hidp_input_report(session, skb);

		if (session->hid)
			hid_input_report(session->hid, HID_INPUT_REPORT, skb->data, skb->len, 0);

		break;

	case HIDP_DATA_RTYPE_OTHER:
	case HIDP_DATA_RTYPE_OUPUT:
	case HIDP_DATA_RTYPE_FEATURE:
		break;

	default:
		__hidp_send_ctrl_message(session,
			HIDP_TRANS_HANDSHAKE | HIDP_HSHK_ERR_INVALID_PARAMETER, NULL, 0);
	}
}