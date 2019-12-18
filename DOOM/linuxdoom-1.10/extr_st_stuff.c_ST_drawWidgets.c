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
typedef  int /*<<< orphan*/  boolean ;

/* Variables and functions */
 int /*<<< orphan*/  STlib_updateBinIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STlib_updateMultIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STlib_updateNum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STlib_updatePercent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ deathmatch ; 
 int st_armson ; 
 int st_fragson ; 
 scalar_t__ st_statusbaron ; 
 int /*<<< orphan*/ * w_ammo ; 
 int /*<<< orphan*/  w_armor ; 
 int /*<<< orphan*/ * w_arms ; 
 int /*<<< orphan*/  w_armsbg ; 
 int /*<<< orphan*/  w_faces ; 
 int /*<<< orphan*/  w_frags ; 
 int /*<<< orphan*/  w_health ; 
 int /*<<< orphan*/ * w_keyboxes ; 
 int /*<<< orphan*/ * w_maxammo ; 
 int /*<<< orphan*/  w_ready ; 

void ST_drawWidgets(boolean refresh)
{
    int		i;

    // used by w_arms[] widgets
    st_armson = st_statusbaron && !deathmatch;

    // used by w_frags widget
    st_fragson = deathmatch && st_statusbaron; 

    STlib_updateNum(&w_ready, refresh);

    for (i=0;i<4;i++)
    {
	STlib_updateNum(&w_ammo[i], refresh);
	STlib_updateNum(&w_maxammo[i], refresh);
    }

    STlib_updatePercent(&w_health, refresh);
    STlib_updatePercent(&w_armor, refresh);

    STlib_updateBinIcon(&w_armsbg, refresh);

    for (i=0;i<6;i++)
	STlib_updateMultIcon(&w_arms[i], refresh);

    STlib_updateMultIcon(&w_faces, refresh);

    for (i=0;i<3;i++)
	STlib_updateMultIcon(&w_keyboxes[i], refresh);

    STlib_updateNum(&w_frags, refresh);

}