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
typedef  int u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int* phone; int si1; int* eazmsn; int si2; } ;
struct TYPE_4__ {TYPE_1__ setup; } ;
struct l3_process {int debug; int /*<<< orphan*/  st; int /*<<< orphan*/  timer; TYPE_2__ para; int /*<<< orphan*/  callref; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T303 ; 
 int DL_DATA ; 
 int* EncodeASyncParams (int*,int) ; 
 void* EncodeSyncParams (int,int) ; 
 void* IE_BEARER ; 
 int /*<<< orphan*/  IE_CALLED_PN ; 
 int /*<<< orphan*/  IE_CALLED_SUB ; 
 int /*<<< orphan*/  IE_CALLING_PN ; 
 int /*<<< orphan*/  IE_CALLING_SUB ; 
 int /*<<< orphan*/  IE_CHANNEL_ID ; 
 int /*<<< orphan*/  IE_KEYPAD ; 
 void* IE_LLC ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int L3_DEB_WARN ; 
 int /*<<< orphan*/  MT_SETUP ; 
 int /*<<< orphan*/  MsgHead (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REQUEST ; 
 int /*<<< orphan*/  T303 ; 
 int /*<<< orphan*/  isdigit (int) ; 
 struct sk_buff* l3_alloc_skb (int) ; 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  l3_msg (int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ strchr (int*,char) ; 
 int strlen (int*) ; 

__attribute__((used)) static void
l3dss1_setup_req(struct l3_process *pc, u_char pr,
		 void *arg)
{
	struct sk_buff *skb;
	u_char tmp[128];
	u_char *p = tmp;
	u_char channel = 0;

        u_char send_keypad;
	u_char screen = 0x80;
	u_char *teln;
	u_char *msn;
	u_char *sub;
	u_char *sp;
	int l;

	MsgHead(p, pc->callref, MT_SETUP);

	teln = pc->para.setup.phone;
#ifndef CONFIG_HISAX_NO_KEYPAD
        send_keypad = (strchr(teln,'*') || strchr(teln,'#')) ? 1 : 0; 
#else
	send_keypad = 0;
#endif
#ifndef CONFIG_HISAX_NO_SENDCOMPLETE
	if (!send_keypad)
		*p++ = 0xa1;		/* complete indicator */
#endif
	/*
	 * Set Bearer Capability, Map info from 1TR6-convention to EDSS1
	 */
	switch (pc->para.setup.si1) {
	case 1:	                  /* Telephony                                */
		*p++ = IE_BEARER;
		*p++ = 0x3;	  /* Length                                   */
		*p++ = 0x90;	  /* Coding Std. CCITT, 3.1 kHz audio         */
		*p++ = 0x90;	  /* Circuit-Mode 64kbps                      */
		*p++ = 0xa3;	  /* A-Law Audio                              */
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

	if (send_keypad) {
		*p++ = IE_KEYPAD;
		*p++ = strlen(teln);
		while (*teln)
			*p++ = (*teln++) & 0x7F;
	}
	  
	/*
	 * What about info2? Mapping to High-Layer-Compatibility?
	 */
	if ((*teln) && (!send_keypad)) {
		/* parse number for special things */
		if (!isdigit(*teln)) {
			switch (0x5f & *teln) {
				case 'C':
					channel = 0x08;
				case 'P':
					channel |= 0x80;
					teln++;
					if (*teln == '1')
						channel |= 0x01;
					else
						channel |= 0x02;
					break;
				case 'R':
					screen = 0xA0;
					break;
				case 'D':
					screen = 0x80;
					break;
				
			        default:
					if (pc->debug & L3_DEB_WARN)
						l3_debug(pc->st, "Wrong MSN Code");
					break;
			}
			teln++;
		}
	}
	if (channel) {
		*p++ = IE_CHANNEL_ID;
		*p++ = 1;
		*p++ = channel;
	}
	msn = pc->para.setup.eazmsn;
	sub = NULL;
	sp = msn;
	while (*sp) {
		if ('.' == *sp) {
			sub = sp;
			*sp = 0;
		} else
			sp++;
	}
	if (*msn) {
		*p++ = IE_CALLING_PN;
		*p++ = strlen(msn) + (screen ? 2 : 1);
		/* Classify as AnyPref. */
		if (screen) {
			*p++ = 0x01;	/* Ext = '0'B, Type = '000'B, Plan = '0001'B. */
			*p++ = screen;
		} else
			*p++ = 0x81;	/* Ext = '1'B, Type = '000'B, Plan = '0001'B. */
		while (*msn)
			*p++ = *msn++ & 0x7f;
	}
	if (sub) {
		*sub++ = '.';
		*p++ = IE_CALLING_SUB;
		*p++ = strlen(sub) + 2;
		*p++ = 0x80;	/* NSAP coded */
		*p++ = 0x50;	/* local IDI format */
		while (*sub)
			*p++ = *sub++ & 0x7f;
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
	
        if (!send_keypad) {      
		*p++ = IE_CALLED_PN;
		*p++ = strlen(teln) + 1;
		/* Classify as AnyPref. */
		*p++ = 0x81;		/* Ext = '1'B, Type = '000'B, Plan = '0001'B. */
		while (*teln)
			*p++ = *teln++ & 0x7f;
		
		if (sub) {
			*sub++ = '.';
			*p++ = IE_CALLED_SUB;
			*p++ = strlen(sub) + 2;
			*p++ = 0x80;	/* NSAP coded */
			*p++ = 0x50;	/* local IDI format */
			while (*sub)
				*p++ = *sub++ & 0x7f;
		}
        }
#ifdef EXT_BEARER_CAPS
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
#ifndef CONFIG_HISAX_NO_LLC
	} else {
	  switch (pc->para.setup.si1) {
		case 1:	                /* Telephony                                */
			*p++ = IE_LLC;
			*p++ = 0x3;	/* Length                                   */
			*p++ = 0x90;	/* Coding Std. CCITT, 3.1 kHz audio         */
			*p++ = 0x90;	/* Circuit-Mode 64kbps                      */
			*p++ = 0xa3;	/* A-Law Audio                              */
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
#endif
	}
#endif
	l = p - tmp;
	if (!(skb = l3_alloc_skb(l)))
		return;
	memcpy(skb_put(skb, l), tmp, l);
	L3DelTimer(&pc->timer);
	L3AddTimer(&pc->timer, T303, CC_T303);
	newl3state(pc, 1);
	l3_msg(pc->st, DL_DATA | REQUEST, skb);
}