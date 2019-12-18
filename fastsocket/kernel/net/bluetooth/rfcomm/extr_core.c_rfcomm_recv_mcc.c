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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct rfcomm_session {int /*<<< orphan*/  flags; } ;
struct rfcomm_mcc {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int,int) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
#define  RFCOMM_FCOFF 135 
#define  RFCOMM_FCON 134 
#define  RFCOMM_MSC 133 
#define  RFCOMM_NSC 132 
#define  RFCOMM_PN 131 
#define  RFCOMM_RLS 130 
#define  RFCOMM_RPN 129 
#define  RFCOMM_TEST 128 
 int /*<<< orphan*/  RFCOMM_TX_THROTTLED ; 
 int __get_mcc_len (int /*<<< orphan*/ ) ; 
 int __get_mcc_type (int /*<<< orphan*/ ) ; 
 int __test_cr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_recv_msc (struct rfcomm_session*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_recv_pn (struct rfcomm_session*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_recv_rls (struct rfcomm_session*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_recv_rpn (struct rfcomm_session*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_send_fcoff (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_fcon (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_nsc (struct rfcomm_session*,int,int) ; 
 int /*<<< orphan*/  rfcomm_send_test (struct rfcomm_session*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int rfcomm_recv_mcc(struct rfcomm_session *s, struct sk_buff *skb)
{
	struct rfcomm_mcc *mcc = (void *) skb->data;
	u8 type, cr, len;

	cr   = __test_cr(mcc->type);
	type = __get_mcc_type(mcc->type);
	len  = __get_mcc_len(mcc->len);

	BT_DBG("%p type 0x%x cr %d", s, type, cr);

	skb_pull(skb, 2);

	switch (type) {
	case RFCOMM_PN:
		rfcomm_recv_pn(s, cr, skb);
		break;

	case RFCOMM_RPN:
		rfcomm_recv_rpn(s, cr, len, skb);
		break;

	case RFCOMM_RLS:
		rfcomm_recv_rls(s, cr, skb);
		break;

	case RFCOMM_MSC:
		rfcomm_recv_msc(s, cr, skb);
		break;

	case RFCOMM_FCOFF:
		if (cr) {
			set_bit(RFCOMM_TX_THROTTLED, &s->flags);
			rfcomm_send_fcoff(s, 0);
		}
		break;

	case RFCOMM_FCON:
		if (cr) {
			clear_bit(RFCOMM_TX_THROTTLED, &s->flags);
			rfcomm_send_fcon(s, 0);
		}
		break;

	case RFCOMM_TEST:
		if (cr)
			rfcomm_send_test(s, 0, skb->data, skb->len);
		break;

	case RFCOMM_NSC:
		break;

	default:
		BT_ERR("Unknown control type 0x%02x", type);
		rfcomm_send_nsc(s, cr, type);
		break;
	}
	return 0;
}