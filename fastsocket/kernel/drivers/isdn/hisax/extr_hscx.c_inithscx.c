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
struct TYPE_4__ {int hscx; int tsaxr0; int tsaxr1; } ;
struct TYPE_5__ {TYPE_1__ hscx; } ;
struct TYPE_6__ {TYPE_2__ hw; void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_hscxstate ; 
 int /*<<< orphan*/  modehscx (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* setstack_hscx ; 

void
inithscx(struct IsdnCardState *cs)
{
	cs->bcs[0].BC_SetStack = setstack_hscx;
	cs->bcs[1].BC_SetStack = setstack_hscx;
	cs->bcs[0].BC_Close = close_hscxstate;
	cs->bcs[1].BC_Close = close_hscxstate;
	cs->bcs[0].hw.hscx.hscx = 0;
	cs->bcs[1].hw.hscx.hscx = 1;
	cs->bcs[0].hw.hscx.tsaxr0 = 0x2f;
	cs->bcs[0].hw.hscx.tsaxr1 = 3;
	cs->bcs[1].hw.hscx.tsaxr0 = 0x2f;
	cs->bcs[1].hw.hscx.tsaxr1 = 3;
	modehscx(cs->bcs, 0, 0);
	modehscx(cs->bcs + 1, 0, 0);
}