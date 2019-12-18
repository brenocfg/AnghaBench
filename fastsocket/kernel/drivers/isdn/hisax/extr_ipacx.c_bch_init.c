#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct IsdnCardState {TYPE_3__* bcs; } ;
struct TYPE_4__ {int hscx; } ;
struct TYPE_5__ {TYPE_1__ hscx; } ;
struct TYPE_6__ {struct IsdnCardState* cs; TYPE_2__ hw; int /*<<< orphan*/  BC_Close; int /*<<< orphan*/  BC_SetStack; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_close_state ; 
 int /*<<< orphan*/  bch_mode (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bch_setstack ; 

__attribute__((used)) static void
bch_init(struct IsdnCardState *cs, int hscx)
{
	cs->bcs[hscx].BC_SetStack   = bch_setstack;
	cs->bcs[hscx].BC_Close      = bch_close_state;
	cs->bcs[hscx].hw.hscx.hscx  = hscx;
	cs->bcs[hscx].cs            = cs;
	bch_mode(cs->bcs + hscx, 0, hscx);
}