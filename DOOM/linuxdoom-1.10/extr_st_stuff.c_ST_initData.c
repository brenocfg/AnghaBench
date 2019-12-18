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
struct TYPE_3__ {int /*<<< orphan*/ * weaponowned; } ;

/* Variables and functions */
 int /*<<< orphan*/  FirstPersonState ; 
 int NUMWEAPONS ; 
 int /*<<< orphan*/  STlib_init () ; 
 int /*<<< orphan*/  StartChatState ; 
 size_t consoleplayer ; 
 int* keyboxes ; 
 int /*<<< orphan*/ * oldweaponsowned ; 
 TYPE_1__* players ; 
 TYPE_1__* plyr ; 
 int st_chat ; 
 int /*<<< orphan*/  st_chatstate ; 
 scalar_t__ st_clock ; 
 int st_cursoron ; 
 scalar_t__ st_faceindex ; 
 int st_firsttime ; 
 int /*<<< orphan*/  st_gamestate ; 
 int st_oldchat ; 
 int st_oldhealth ; 
 int st_palette ; 
 int st_statusbaron ; 

void ST_initData(void)
{

    int		i;

    st_firsttime = true;
    plyr = &players[consoleplayer];

    st_clock = 0;
    st_chatstate = StartChatState;
    st_gamestate = FirstPersonState;

    st_statusbaron = true;
    st_oldchat = st_chat = false;
    st_cursoron = false;

    st_faceindex = 0;
    st_palette = -1;

    st_oldhealth = -1;

    for (i=0;i<NUMWEAPONS;i++)
	oldweaponsowned[i] = plyr->weaponowned[i];

    for (i=0;i<3;i++)
	keyboxes[i] = -1;

    STlib_init();

}