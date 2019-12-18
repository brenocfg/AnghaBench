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
typedef  char u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {char* phone; int si1; int si2; } ;
struct TYPE_4__ {TYPE_1__ setup; } ;
struct l3_process {int /*<<< orphan*/  st; int /*<<< orphan*/  timer; TYPE_2__ para; int /*<<< orphan*/  callref; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T303 ; 
 int DL_DATA ; 
 char* EncodeASyncParams (char*,int) ; 
 void* EncodeSyncParams (int,int) ; 
 void* IE_BEARER ; 
 int /*<<< orphan*/  IE_KEYPAD ; 
 void* IE_LLC ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MT_SETUP ; 
 int /*<<< orphan*/  MsgHead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int /*<<< orphan*/  T303 ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
l3ni1_setup_req(struct l3_process *pc, u_char pr,
		 void *arg)
{
	struct sk_buff *skb;
	u_char tmp[128];
	u_char *p = tmp;

	u_char *teln;
	u_char *sub;
	u_char *sp;
	int l;

	MsgHead(p, pc->callref, MT_SETUP);

	teln = pc->para.setup.phone;

	*p++ = 0xa1;		/* complete indicator */
	/*
	 * Set Bearer Capability, Map info from 1TR6-convention to NI1
	 */
	switch (pc->para.setup.si1) {
	case 1:	                  /* Telephony                                */
		*p++ = IE_BEARER;
		*p++ = 0x3;	  /* Length                                   */
		*p++ = 0x90;	  /* 3.1khz Audio      			      */
		*p++ = 0x90;	  /* Circuit-Mode 64kbps                      */
		*p++ = 0xa2;	  /* u-Law Audio                              */
		break;
	case 5:	                  /* Datatransmission 64k, BTX                */
	case 7:	                  /* Datatransmission 64k                     */
	default:
		*p++ = IE_BEARER;
		*p++ = 0x2;	  /* Length                                   */
		*p++ = 0x88;	  /* Coding Std. CCITT, unrestr. dig. Inform. */
		*p++ = 0x90;	  /* Circuit-Mode 64kbps                      */
		break;
	}

	sub = NULL;
	sp = teln;
	while (*sp) {
		if ('.' == *sp) {
			sub = sp;
			*sp = 0;
		} else
			sp++;
	}
	
	*p++ = IE_KEYPAD;
	*p++ = strlen(teln);
	while (*teln)
		*p++ = (*teln++) & 0x7F;

	if (sub)
		*sub++ = '.';
	
#if EXT_BEARER_CAPS
	if ((pc->para.setup.si2 >= 160) && (pc->para.setup.si2 <= 175)) {	// sync. Bitratenadaption, V.110/X.30

		*p++ = IE_LLC;
		*p++ = 0x04;
		*p++ = 0x88;
		*p++ = 0x90;
		*p++ = 0x21;
		*p++ = EncodeSyncParams(pc->para.setup.si2 - 160, 0x80);
	} else if ((pc->para.setup.si2 >= 176) && (pc->para.setup.si2 <= 191)) {	// sync. Bitratenadaption, V.120

		*p++ = IE_LLC;
		*p++ = 0x05;
		*p++ = 0x88;
		*p++ = 0x90;
		*p++ = 0x28;
		*p++ = EncodeSyncParams(pc->para.setup.si2 - 176, 0);
		*p++ = 0x82;
	} else if (pc->para.setup.si2 >= 192) {		// async. Bitratenadaption, V.110/X.30

		*p++ = IE_LLC;
		*p++ = 0x06;
		*p++ = 0x88;
		*p++ = 0x90;
		*p++ = 0x21;
		p = EncodeASyncParams(p, pc->para.setup.si2 - 192);
	} else {
	  switch (pc->para.setup.si1) {
		case 1:	                /* Telephony                                */
			*p++ = IE_LLC;
			*p++ = 0x3;	/* Length                                   */
			*p++ = 0x90;	/* Coding Std. CCITT, 3.1 kHz audio         */
			*p++ = 0x90;	/* Circuit-Mode 64kbps                      */
			*p++ = 0xa2;	/* u-Law Audio                              */
			break;
		case 5:	                /* Datatransmission 64k, BTX                */
		case 7:	                /* Datatransmission 64k                     */
		default:
			*p++ = IE_LLC;
			*p++ = 0x2;	/* Length                                   */
			*p++ = 0x88;	/* Coding Std. CCITT, unrestr. dig. Inform. */
			*p++ = 0x90;	/* Circuit-Mode 64kbps                      */
			break;
	  }
	}
#endif
	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
{
		return;
}
	memcpy(skb_put(skb, l), tmp, l);
	L3DelTimer(&pc->timer);
	L3AddTimer(&pc->timer, T303, CC_T303);
	newl3state(pc, 1);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}