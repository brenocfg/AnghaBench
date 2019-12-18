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
struct TYPE_3__ {int actionflags; scalar_t__ speed; int /*<<< orphan*/  dir; scalar_t__ thinktime; } ;
typedef  TYPE_1__ bot_input_t ;

/* Variables and functions */
 int ACTION_JUMP ; 
 int ACTION_JUMPEDLASTFRAME ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 TYPE_1__* botinputs ; 
 int qfalse ; 

void EA_ResetInput(int client)
{
	bot_input_t *bi;
	int jumped = qfalse;

	bi = &botinputs[client];
	bi->actionflags &= ~ACTION_JUMPEDLASTFRAME;

	bi->thinktime = 0;
	VectorClear(bi->dir);
	bi->speed = 0;
	jumped = bi->actionflags & ACTION_JUMP;
	bi->actionflags = 0;
	if (jumped) bi->actionflags |= ACTION_JUMPEDLASTFRAME;
}