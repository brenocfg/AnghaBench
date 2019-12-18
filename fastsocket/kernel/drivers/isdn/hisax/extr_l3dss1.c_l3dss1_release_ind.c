#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sk_buff {int* data; int /*<<< orphan*/  len; } ;
struct l3_process {TYPE_2__* st; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_2__*,int,struct l3_process*) ;} ;
struct TYPE_5__ {TYPE_1__ l3; } ;

/* Variables and functions */
 int CC_IGNORE ; 
 int CC_RELEASE ; 
 int /*<<< orphan*/  IE_CALL_STATE ; 
 int INDICATION ; 
 int /*<<< orphan*/  dss1_release_l3_process (struct l3_process*) ; 
 int* findie (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,struct l3_process*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3dss1_release_ind(struct l3_process *pc, u_char pr, void *arg)
{
	u_char *p;
	struct sk_buff *skb = arg;
	int callState = 0;
	p = skb->data;

	if ((p = findie(p, skb->len, IE_CALL_STATE, 0))) {
		p++;
		if (1 == *p++)
			callState = *p;
	}
	if (callState == 0) {
		/* ETS 300-104 7.6.1, 8.6.1, 10.6.1... and 16.1
		 * set down layer 3 without sending any message
		 */
		pc->st->l3.l3l4(pc->st, CC_RELEASE | INDICATION, pc);
		newl3state(pc, 0);
		dss1_release_l3_process(pc);
	} else {
		pc->st->l3.l3l4(pc->st, CC_IGNORE | INDICATION, pc);
	}
}