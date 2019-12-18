#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int cause; } ;
struct l3_process {int debug; TYPE_3__* st; TYPE_1__ para; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int,struct l3_process*) ;} ;
struct TYPE_7__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int CC_PROGRESS ; 
 int ERR_IE_COMPREHENSION ; 
 int /*<<< orphan*/  IE_PROGRESS ; 
 int INDICATION ; 
 int L3_DEB_WARN ; 
 int check_infoelements (struct l3_process*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int* findie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_PROGRESS ; 
 int /*<<< orphan*/  l3_debug (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  l3ni1_status_send (struct l3_process*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3ni1_std_ie_err (struct l3_process*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_progress(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	int err = 0;
	u_char *p;

	if ((p = findie(skb->data, skb->len, IE_PROGRESS, 0))) {
		if (p[1] != 2) {
			err = 1;
			pc->para.cause = 100;
		} else if (!(p[2] & 0x70)) {
			switch (p[2]) {
				case 0x80:
				case 0x81:
				case 0x82:
				case 0x84:
				case 0x85:
				case 0x87:
				case 0x8a:
					switch (p[3]) {
						case 0x81:
						case 0x82:
						case 0x83:
						case 0x84:
						case 0x88:
							break;
						default:
							err = 2;
							pc->para.cause = 100;
							break;
					}
					break;
				default:
					err = 3;
					pc->para.cause = 100;
					break;
			}
		}
	} else {
		pc->para.cause = 96;
		err = 4;
	}
	if (err) {	
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "progress error %d", err);
		l3ni1_status_send(pc, pr, NULL);
		return;
	}
	/* Now we are on none mandatory IEs */
	err = check_infoelements(pc, skb, ie_PROGRESS);
	if (err)
		l3ni1_std_ie_err(pc, err);
	if (ERR_IE_COMPREHENSION != err)
		pc->st->l3.l3l4(pc->st, CC_PROGRESS | INDICATION, pc);
}