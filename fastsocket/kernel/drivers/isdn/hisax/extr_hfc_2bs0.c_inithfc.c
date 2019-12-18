#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct IsdnCardState {TYPE_1__* bcs; int /*<<< orphan*/ * BC_Send_Data; } ;
struct TYPE_3__ {void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_hfcstate ; 
 int /*<<< orphan*/  hfc_fill_fifo ; 
 int /*<<< orphan*/  init_send (TYPE_1__*) ; 
 int /*<<< orphan*/  mode_hfc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* setstack_hfc ; 

void
inithfc(struct IsdnCardState *cs)
{
	init_send(&cs->bcs[0]);
	init_send(&cs->bcs[1]);
	cs->BC_Send_Data = &hfc_fill_fifo;
	cs->bcs[0].BC_SetStack = setstack_hfc;
	cs->bcs[1].BC_SetStack = setstack_hfc;
	cs->bcs[0].BC_Close = close_hfcstate;
	cs->bcs[1].BC_Close = close_hfcstate;
	mode_hfc(cs->bcs, 0, 0);
	mode_hfc(cs->bcs + 1, 0, 0);
}