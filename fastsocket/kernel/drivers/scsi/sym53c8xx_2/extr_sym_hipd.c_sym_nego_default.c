#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int check_nego; int /*<<< orphan*/  qas; int /*<<< orphan*/  dt; int /*<<< orphan*/  iu; int /*<<< orphan*/  offset; int /*<<< orphan*/  period; } ;
struct sym_tcb {TYPE_1__ tgoal; } ;
struct sym_hcb {void** msgout; void** msgin; int /*<<< orphan*/  maxoffs; int /*<<< orphan*/  minsync; } ;
struct sym_ccb {int nego_status; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 void* M_NOOP ; 
#define  NS_PPR 130 
#define  NS_SYNC 129 
#define  NS_WIDE 128 
 int /*<<< orphan*/  sym_setpprot (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_setsync (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_setwide (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_nego_default(struct sym_hcb *np, struct sym_tcb *tp, struct sym_ccb *cp)
{
	switch (cp->nego_status) {
	case NS_PPR:
#if 0
		sym_setpprot (np, cp->target, 0, 0, 0, 0, 0, 0);
#else
		if (tp->tgoal.period < np->minsync)
			tp->tgoal.period = np->minsync;
		if (tp->tgoal.offset > np->maxoffs)
			tp->tgoal.offset = np->maxoffs;
		tp->tgoal.iu = tp->tgoal.dt = tp->tgoal.qas = 0;
		tp->tgoal.check_nego = 1;
#endif
		break;
	case NS_SYNC:
		sym_setsync (np, cp->target, 0, 0, 0, 0);
		break;
	case NS_WIDE:
		sym_setwide (np, cp->target, 0);
		break;
	}
	np->msgin [0] = M_NOOP;
	np->msgout[0] = M_NOOP;
	cp->nego_status = 0;
}