#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t readyweapon; int /*<<< orphan*/ * maxammo; int /*<<< orphan*/ * ammo; int /*<<< orphan*/  armorpoints; int /*<<< orphan*/ * weaponowned; int /*<<< orphan*/  health; } ;
struct TYPE_9__ {size_t data; } ;
struct TYPE_8__ {size_t ammo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_AMMO0WIDTH ; 
 int /*<<< orphan*/  ST_AMMO0X ; 
 int /*<<< orphan*/  ST_AMMO0Y ; 
 int /*<<< orphan*/  ST_AMMO1WIDTH ; 
 int /*<<< orphan*/  ST_AMMO1X ; 
 int /*<<< orphan*/  ST_AMMO1Y ; 
 int /*<<< orphan*/  ST_AMMO2WIDTH ; 
 int /*<<< orphan*/  ST_AMMO2X ; 
 int /*<<< orphan*/  ST_AMMO2Y ; 
 int /*<<< orphan*/  ST_AMMO3WIDTH ; 
 int /*<<< orphan*/  ST_AMMO3X ; 
 int /*<<< orphan*/  ST_AMMO3Y ; 
 int /*<<< orphan*/  ST_AMMOWIDTH ; 
 int /*<<< orphan*/  ST_AMMOX ; 
 int /*<<< orphan*/  ST_AMMOY ; 
 int /*<<< orphan*/  ST_ARMORX ; 
 int /*<<< orphan*/  ST_ARMORY ; 
 int /*<<< orphan*/  ST_ARMSBGX ; 
 int /*<<< orphan*/  ST_ARMSBGY ; 
 scalar_t__ ST_ARMSX ; 
 int ST_ARMSXSPACE ; 
 scalar_t__ ST_ARMSY ; 
 int ST_ARMSYSPACE ; 
 scalar_t__ ST_FACESX ; 
 scalar_t__ ST_FACESY ; 
 int /*<<< orphan*/  ST_FRAGSWIDTH ; 
 int /*<<< orphan*/  ST_FRAGSX ; 
 int /*<<< orphan*/  ST_FRAGSY ; 
 int /*<<< orphan*/  ST_HEALTHX ; 
 int /*<<< orphan*/  ST_HEALTHY ; 
 scalar_t__ ST_KEY0X ; 
 scalar_t__ ST_KEY0Y ; 
 scalar_t__ ST_KEY1X ; 
 scalar_t__ ST_KEY1Y ; 
 scalar_t__ ST_KEY2X ; 
 scalar_t__ ST_KEY2Y ; 
 int /*<<< orphan*/  ST_MAXAMMO0WIDTH ; 
 int /*<<< orphan*/  ST_MAXAMMO0X ; 
 int /*<<< orphan*/  ST_MAXAMMO0Y ; 
 int /*<<< orphan*/  ST_MAXAMMO1WIDTH ; 
 int /*<<< orphan*/  ST_MAXAMMO1X ; 
 int /*<<< orphan*/  ST_MAXAMMO1Y ; 
 int /*<<< orphan*/  ST_MAXAMMO2WIDTH ; 
 int /*<<< orphan*/  ST_MAXAMMO2X ; 
 int /*<<< orphan*/  ST_MAXAMMO2Y ; 
 int /*<<< orphan*/  ST_MAXAMMO3WIDTH ; 
 int /*<<< orphan*/  ST_MAXAMMO3X ; 
 int /*<<< orphan*/  ST_MAXAMMO3Y ; 
 int /*<<< orphan*/  STlib_initBinIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STlib_initMultIcon (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STlib_initNum (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STlib_initPercent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * arms ; 
 int /*<<< orphan*/  armsbg ; 
 int /*<<< orphan*/  faces ; 
 int* keyboxes ; 
 int /*<<< orphan*/  keys ; 
 TYPE_6__* plyr ; 
 int /*<<< orphan*/  shortnum ; 
 int /*<<< orphan*/  st_armson ; 
 int st_faceindex ; 
 int /*<<< orphan*/  st_fragscount ; 
 int /*<<< orphan*/  st_fragson ; 
 int /*<<< orphan*/  st_notdeathmatch ; 
 int /*<<< orphan*/  st_statusbaron ; 
 int /*<<< orphan*/  tallnum ; 
 int /*<<< orphan*/  tallpercent ; 
 TYPE_2__* w_ammo ; 
 int /*<<< orphan*/  w_armor ; 
 int /*<<< orphan*/ * w_arms ; 
 int /*<<< orphan*/  w_armsbg ; 
 int /*<<< orphan*/  w_faces ; 
 TYPE_2__ w_frags ; 
 int /*<<< orphan*/  w_health ; 
 int /*<<< orphan*/ * w_keyboxes ; 
 TYPE_2__* w_maxammo ; 
 TYPE_2__ w_ready ; 
 TYPE_1__* weaponinfo ; 

void ST_createWidgets(void)
{

    int i;

    // ready weapon ammo
    STlib_initNum(&w_ready,
		  ST_AMMOX,
		  ST_AMMOY,
		  tallnum,
		  &plyr->ammo[weaponinfo[plyr->readyweapon].ammo],
		  &st_statusbaron,
		  ST_AMMOWIDTH );

    // the last weapon type
    w_ready.data = plyr->readyweapon; 

    // health percentage
    STlib_initPercent(&w_health,
		      ST_HEALTHX,
		      ST_HEALTHY,
		      tallnum,
		      &plyr->health,
		      &st_statusbaron,
		      tallpercent);

    // arms background
    STlib_initBinIcon(&w_armsbg,
		      ST_ARMSBGX,
		      ST_ARMSBGY,
		      armsbg,
		      &st_notdeathmatch,
		      &st_statusbaron);

    // weapons owned
    for(i=0;i<6;i++)
    {
	STlib_initMultIcon(&w_arms[i],
			   ST_ARMSX+(i%3)*ST_ARMSXSPACE,
			   ST_ARMSY+(i/3)*ST_ARMSYSPACE,
			   arms[i], (int *) &plyr->weaponowned[i+1],
			   &st_armson);
    }

    // frags sum
    STlib_initNum(&w_frags,
		  ST_FRAGSX,
		  ST_FRAGSY,
		  tallnum,
		  &st_fragscount,
		  &st_fragson,
		  ST_FRAGSWIDTH);

    // faces
    STlib_initMultIcon(&w_faces,
		       ST_FACESX,
		       ST_FACESY,
		       faces,
		       &st_faceindex,
		       &st_statusbaron);

    // armor percentage - should be colored later
    STlib_initPercent(&w_armor,
		      ST_ARMORX,
		      ST_ARMORY,
		      tallnum,
		      &plyr->armorpoints,
		      &st_statusbaron, tallpercent);

    // keyboxes 0-2
    STlib_initMultIcon(&w_keyboxes[0],
		       ST_KEY0X,
		       ST_KEY0Y,
		       keys,
		       &keyboxes[0],
		       &st_statusbaron);
    
    STlib_initMultIcon(&w_keyboxes[1],
		       ST_KEY1X,
		       ST_KEY1Y,
		       keys,
		       &keyboxes[1],
		       &st_statusbaron);

    STlib_initMultIcon(&w_keyboxes[2],
		       ST_KEY2X,
		       ST_KEY2Y,
		       keys,
		       &keyboxes[2],
		       &st_statusbaron);

    // ammo count (all four kinds)
    STlib_initNum(&w_ammo[0],
		  ST_AMMO0X,
		  ST_AMMO0Y,
		  shortnum,
		  &plyr->ammo[0],
		  &st_statusbaron,
		  ST_AMMO0WIDTH);

    STlib_initNum(&w_ammo[1],
		  ST_AMMO1X,
		  ST_AMMO1Y,
		  shortnum,
		  &plyr->ammo[1],
		  &st_statusbaron,
		  ST_AMMO1WIDTH);

    STlib_initNum(&w_ammo[2],
		  ST_AMMO2X,
		  ST_AMMO2Y,
		  shortnum,
		  &plyr->ammo[2],
		  &st_statusbaron,
		  ST_AMMO2WIDTH);
    
    STlib_initNum(&w_ammo[3],
		  ST_AMMO3X,
		  ST_AMMO3Y,
		  shortnum,
		  &plyr->ammo[3],
		  &st_statusbaron,
		  ST_AMMO3WIDTH);

    // max ammo count (all four kinds)
    STlib_initNum(&w_maxammo[0],
		  ST_MAXAMMO0X,
		  ST_MAXAMMO0Y,
		  shortnum,
		  &plyr->maxammo[0],
		  &st_statusbaron,
		  ST_MAXAMMO0WIDTH);

    STlib_initNum(&w_maxammo[1],
		  ST_MAXAMMO1X,
		  ST_MAXAMMO1Y,
		  shortnum,
		  &plyr->maxammo[1],
		  &st_statusbaron,
		  ST_MAXAMMO1WIDTH);

    STlib_initNum(&w_maxammo[2],
		  ST_MAXAMMO2X,
		  ST_MAXAMMO2Y,
		  shortnum,
		  &plyr->maxammo[2],
		  &st_statusbaron,
		  ST_MAXAMMO2WIDTH);
    
    STlib_initNum(&w_maxammo[3],
		  ST_MAXAMMO3X,
		  ST_MAXAMMO3Y,
		  shortnum,
		  &plyr->maxammo[3],
		  &st_statusbaron,
		  ST_MAXAMMO3WIDTH);

}