#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct TYPE_7__ {int si1; char* eazmsn; int plan; char* phone; int screen; scalar_t__ si2; } ;
struct TYPE_8__ {int moderate; int cause; int bchannel; TYPE_2__ setup; } ;
struct l3_process {int debug; TYPE_4__* st; TYPE_3__ para; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_4__*,int,struct l3_process*) ;} ;
struct TYPE_9__ {TYPE_1__ l3; } ;

/* Variables and functions */
 int CC_SETUP ; 
 scalar_t__ DecodeSI2 (struct sk_buff*) ; 
 int ERR_IE_COMPREHENSION ; 
 int INDICATION ; 
 int L3_DEB_SI ; 
 int L3_DEB_WARN ; 
 int check_infoelements (struct l3_process*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int* findie (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_SETUP ; 
 int /*<<< orphan*/  iecpy (char*,int*,int) ; 
 int /*<<< orphan*/  l3_debug (TYPE_4__*,char*,...) ; 
 int l3dss1_get_channel_id (struct l3_process*,struct sk_buff*) ; 
 int /*<<< orphan*/  l3dss1_msg_without_setup (struct l3_process*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3dss1_std_ie_err (struct l3_process*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3dss1_setup(struct l3_process *pc, u_char pr, void *arg)
{
	u_char *p;
	int bcfound = 0;
	char tmp[80];
	struct sk_buff *skb = arg;
	int id;
	int err = 0;

	/*
	 * Bearer Capabilities
	 */
	p = skb->data;
	/* only the first occurence 'll be detected ! */
	if ((p = findie(p, skb->len, 0x04, 0))) {
		if ((p[1] < 2) || (p[1] > 11))
			err = 1;
		else {
			pc->para.setup.si2 = 0;
			switch (p[2] & 0x7f) {
				case 0x00: /* Speech */
				case 0x10: /* 3.1 Khz audio */
					pc->para.setup.si1 = 1;
					break;
				case 0x08: /* Unrestricted digital information */
					pc->para.setup.si1 = 7;
/* JIM, 05.11.97 I wanna set service indicator 2 */
#ifdef EXT_BEARER_CAPS
					pc->para.setup.si2 = DecodeSI2(skb);
#endif
					break;
				case 0x09: /* Restricted digital information */
					pc->para.setup.si1 = 2;
					break;
				case 0x11:
					/* Unrestr. digital information  with 
					 * tones/announcements ( or 7 kHz audio
					 */
					pc->para.setup.si1 = 3;
					break;
				case 0x18: /* Video */
					pc->para.setup.si1 = 4;
					break;
				default:
					err = 2;
					break;
			}
			switch (p[3] & 0x7f) {
				case 0x40: /* packed mode */
					pc->para.setup.si1 = 8;
					break;
				case 0x10: /* 64 kbit */
				case 0x11: /* 2*64 kbit */
				case 0x13: /* 384 kbit */
				case 0x15: /* 1536 kbit */
				case 0x17: /* 1920 kbit */
					pc->para.moderate = p[3] & 0x7f;
					break;
				default:
					err = 3;
					break;
			}
		}
		if (pc->debug & L3_DEB_SI)
			l3_debug(pc->st, "SI=%d, AI=%d",
				pc->para.setup.si1, pc->para.setup.si2);
		if (err) {
			if (pc->debug & L3_DEB_WARN)
				l3_debug(pc->st, "setup with wrong bearer(l=%d:%x,%x)",
					p[1], p[2], p[3]);
			pc->para.cause = 100;
			l3dss1_msg_without_setup(pc, pr, NULL);
			return;
		}
	} else {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "setup without bearer capabilities");
		/* ETS 300-104 1.3.3 */
		pc->para.cause = 96;
		l3dss1_msg_without_setup(pc, pr, NULL);
		return;
	}
	/*
	 * Channel Identification
	 */
	if ((id = l3dss1_get_channel_id(pc, skb)) >= 0) {
		if ((pc->para.bchannel = id)) {
			if ((3 == id) && (0x10 == pc->para.moderate)) {
				if (pc->debug & L3_DEB_WARN)
					l3_debug(pc->st, "setup with wrong chid %x",
						id);
				pc->para.cause = 100;
				l3dss1_msg_without_setup(pc, pr, NULL);
				return;
			}
			bcfound++;
		} else 
                   { if (pc->debug & L3_DEB_WARN)
			 l3_debug(pc->st, "setup without bchannel, call waiting");
                     bcfound++;
                   } 
	} else {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "setup with wrong chid ret %d", id);
		if (id == -1)
			pc->para.cause = 96;
		else
			pc->para.cause = 100;
		l3dss1_msg_without_setup(pc, pr, NULL);
		return;
	}
	/* Now we are on none mandatory IEs */
	err = check_infoelements(pc, skb, ie_SETUP);
	if (ERR_IE_COMPREHENSION == err) {
		pc->para.cause = 96;
		l3dss1_msg_without_setup(pc, pr, NULL);
		return;
	}
	p = skb->data;
	if ((p = findie(p, skb->len, 0x70, 0)))
		iecpy(pc->para.setup.eazmsn, p, 1);
	else
		pc->para.setup.eazmsn[0] = 0;

	p = skb->data;
	if ((p = findie(p, skb->len, 0x71, 0))) {
		/* Called party subaddress */
		if ((p[1] >= 2) && (p[2] == 0x80) && (p[3] == 0x50)) {
			tmp[0] = '.';
			iecpy(&tmp[1], p, 2);
			strcat(pc->para.setup.eazmsn, tmp);
		} else if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "wrong called subaddress");
	}
	p = skb->data;
	if ((p = findie(p, skb->len, 0x6c, 0))) {
		pc->para.setup.plan = p[2];
		if (p[2] & 0x80) {
			iecpy(pc->para.setup.phone, p, 1);
			pc->para.setup.screen = 0;
		} else {
			iecpy(pc->para.setup.phone, p, 2);
			pc->para.setup.screen = p[3];
		}
	} else {
		pc->para.setup.phone[0] = 0;
		pc->para.setup.plan = 0;
		pc->para.setup.screen = 0;
	}
	p = skb->data;
	if ((p = findie(p, skb->len, 0x6d, 0))) {
		/* Calling party subaddress */
		if ((p[1] >= 2) && (p[2] == 0x80) && (p[3] == 0x50)) {
			tmp[0] = '.';
			iecpy(&tmp[1], p, 2);
			strcat(pc->para.setup.phone, tmp);
		} else if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "wrong calling subaddress");
	}
	newl3state(pc, 6);
	if (err) /* STATUS for none mandatory IE errors after actions are taken */
		l3dss1_std_ie_err(pc, err);
	pc->st->l3.l3l4(pc->st, CC_SETUP | INDICATION, pc);
}