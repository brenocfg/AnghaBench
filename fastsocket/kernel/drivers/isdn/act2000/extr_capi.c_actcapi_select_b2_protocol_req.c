#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_11__ {int len; int dlen; int laa; int lab; int win; int modulo; } ;
struct TYPE_7__ {int protocol; TYPE_5__ dlpd; int /*<<< orphan*/  plci; } ;
struct TYPE_8__ {TYPE_1__ select_b2_protocol_req; } ;
struct TYPE_9__ {TYPE_2__ msg; } ;
typedef  TYPE_3__ actcapi_msg ;
struct TYPE_10__ {int l2prot; int /*<<< orphan*/  plci; } ;
typedef  TYPE_4__ act2000_chan ;
typedef  int /*<<< orphan*/  act2000_card ;

/* Variables and functions */
 int /*<<< orphan*/  ACTCAPI_CHKSKB ; 
 int /*<<< orphan*/  ACTCAPI_MKHDR (int,int,int) ; 
 int /*<<< orphan*/  ACTCAPI_QUEUE_TX ; 
#define  ISDN_PROTO_L2_HDLC 132 
#define  ISDN_PROTO_L2_TRANS 131 
#define  ISDN_PROTO_L2_X75BUI 130 
#define  ISDN_PROTO_L2_X75I 129 
#define  ISDN_PROTO_L2_X75UI 128 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void
actcapi_select_b2_protocol_req(act2000_card *card, act2000_chan *chan)
{
	actcapi_msg *m;
	struct sk_buff *skb;

	ACTCAPI_MKHDR(10, 0x40, 0x00);
	ACTCAPI_CHKSKB;
	m->msg.select_b2_protocol_req.plci = chan->plci;
	memset(&m->msg.select_b2_protocol_req.dlpd, 0,
	       sizeof(m->msg.select_b2_protocol_req.dlpd));
	m->msg.select_b2_protocol_req.dlpd.len = 6;
	switch (chan->l2prot) {
		case ISDN_PROTO_L2_TRANS:
			m->msg.select_b2_protocol_req.protocol = 0x03;
			m->msg.select_b2_protocol_req.dlpd.dlen = 4000;
			break;
		case ISDN_PROTO_L2_HDLC:
			m->msg.select_b2_protocol_req.protocol = 0x02;
			m->msg.select_b2_protocol_req.dlpd.dlen = 4000;
			break;
		case ISDN_PROTO_L2_X75I:
		case ISDN_PROTO_L2_X75UI:
		case ISDN_PROTO_L2_X75BUI:
			m->msg.select_b2_protocol_req.protocol = 0x01;
			m->msg.select_b2_protocol_req.dlpd.dlen = 4000;
			m->msg.select_b2_protocol_req.dlpd.laa = 3;
			m->msg.select_b2_protocol_req.dlpd.lab = 1;
			m->msg.select_b2_protocol_req.dlpd.win = 7;
			m->msg.select_b2_protocol_req.dlpd.modulo = 8;
			break;
	}
	ACTCAPI_QUEUE_TX;
}