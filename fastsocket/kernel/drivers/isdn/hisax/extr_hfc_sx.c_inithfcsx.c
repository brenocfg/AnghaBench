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
struct IsdnCardState {TYPE_1__* bcs; int /*<<< orphan*/ * BC_Send_Data; int /*<<< orphan*/  setstack_d; } ;
struct TYPE_2__ {void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_hfcsx ; 
 int /*<<< orphan*/  hfcsx_send_data ; 
 int /*<<< orphan*/  mode_hfcsx (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* setstack_2b ; 
 int /*<<< orphan*/  setstack_hfcsx ; 

__attribute__((used)) static void inithfcsx(struct IsdnCardState *cs)
{
	cs->setstack_d = setstack_hfcsx;
	cs->BC_Send_Data = &hfcsx_send_data;
	cs->bcs[0].BC_SetStack = setstack_2b;
	cs->bcs[1].BC_SetStack = setstack_2b;
	cs->bcs[0].BC_Close = close_hfcsx;
	cs->bcs[1].BC_Close = close_hfcsx;
	mode_hfcsx(cs->bcs, 0, 0);
	mode_hfcsx(cs->bcs + 1, 0, 1);
}