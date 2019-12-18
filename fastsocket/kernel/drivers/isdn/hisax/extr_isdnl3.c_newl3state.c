#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct l3_process {int debug; int callref; int state; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int L3_DEB_STATE ; 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*,int,int,int) ; 

void
newl3state(struct l3_process *pc, int state)
{
	if (pc->debug & L3_DEB_STATE)
		l3_debug(pc->st, "newstate cr %d %d --> %d", 
			 pc->callref & 0x7F,
			 pc->state, state);
	pc->state = state;
}