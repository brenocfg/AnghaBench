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

/* Variables and functions */

void EA_EndRegular(int client, float thinktime)
{
/*
	bot_input_t *bi;
	int jumped = qfalse;

	bi = &botinputs[client];

	bi->actionflags &= ~ACTION_JUMPEDLASTFRAME;

	bi->thinktime = thinktime;
	botimport.BotInput(client, bi);

	bi->thinktime = 0;
	VectorClear(bi->dir);
	bi->speed = 0;
	jumped = bi->actionflags & ACTION_JUMP;
	bi->actionflags = 0;
	if (jumped) bi->actionflags |= ACTION_JUMPEDLASTFRAME;
*/
}