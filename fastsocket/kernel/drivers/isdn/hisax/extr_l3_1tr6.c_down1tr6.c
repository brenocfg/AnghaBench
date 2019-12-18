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
struct TYPE_5__ {int /*<<< orphan*/  setup; } ;
struct l3_process {int callref; int state; TYPE_1__ para; struct Channel* chan; } ;
struct TYPE_6__ {int debug; } ;
struct PStack {TYPE_2__ l3; } ;
struct Channel {int /*<<< orphan*/  setup; struct l3_process* proc; } ;
typedef  int /*<<< orphan*/  setup_parm ;
struct TYPE_7__ {int primitive; int state; int /*<<< orphan*/  (* rout ) (struct l3_process*,int,void*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int CC_SETUP ; 
 int DL_ESTABLISH ; 
 int L3_DEB_STATE ; 
 int REQUEST ; 
 TYPE_3__* downstl ; 
 int /*<<< orphan*/  l3_debug (struct PStack*,char*) ; 
 int /*<<< orphan*/  l3_msg (struct PStack*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct l3_process* new_l3_process (struct PStack*,int) ; 
 int newcallref () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct l3_process*,int,void*) ; 

__attribute__((used)) static void
down1tr6(struct PStack *st, int pr, void *arg)
{
	int i, cr;
	struct l3_process *proc;
	struct Channel *chan;
	char tmp[80];

	if ((DL_ESTABLISH | REQUEST)== pr) {
		l3_msg(st, pr, NULL);
		return;
	} else if ((CC_SETUP | REQUEST) == pr) {
		chan = arg;
		cr = newcallref();
		cr |= 0x80;
		if (!(proc = new_l3_process(st, cr))) {
			return;
		} else {
			proc->chan = chan;
			chan->proc = proc;
			memcpy(&proc->para.setup, &chan->setup, sizeof(setup_parm));
			proc->callref = cr;
		}
	} else {
		proc = arg;
	}

	for (i = 0; i < ARRAY_SIZE(downstl); i++)
		if ((pr == downstl[i].primitive) &&
		    ((1 << proc->state) & downstl[i].state))
			break;
	if (i == ARRAY_SIZE(downstl)) {
		if (st->l3.debug & L3_DEB_STATE) {
			sprintf(tmp, "down1tr6 state %d prim %d unhandled",
				proc->state, pr);
			l3_debug(st, tmp);
		}
	} else {
		if (st->l3.debug & L3_DEB_STATE) {
			sprintf(tmp, "down1tr6 state %d prim %d",
				proc->state, pr);
			l3_debug(st, tmp);
		}
		downstl[i].rout(proc, pr, arg);
	}
}