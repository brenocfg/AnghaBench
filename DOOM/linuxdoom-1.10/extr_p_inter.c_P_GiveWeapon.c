#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t weapontype_t ;
struct TYPE_6__ {int* weaponowned; size_t pendingweapon; int /*<<< orphan*/  bonuscount; } ;
typedef  TYPE_1__ player_t ;
typedef  int boolean ;
struct TYPE_7__ {scalar_t__ ammo; } ;

/* Variables and functions */
 scalar_t__ BONUSADD ; 
 int P_GiveAmmo (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ am_noammo ; 
 size_t consoleplayer ; 
 int deathmatch ; 
 scalar_t__ netgame ; 
 TYPE_1__* players ; 
 int /*<<< orphan*/  sfx_wpnup ; 
 TYPE_2__* weaponinfo ; 

boolean
P_GiveWeapon
( player_t*	player,
  weapontype_t	weapon,
  boolean	dropped )
{
    boolean	gaveammo;
    boolean	gaveweapon;
	
    if (netgame
	&& (deathmatch!=2)
	 && !dropped )
    {
	// leave placed weapons forever on net games
	if (player->weaponowned[weapon])
	    return false;

	player->bonuscount += BONUSADD;
	player->weaponowned[weapon] = true;

	if (deathmatch)
	    P_GiveAmmo (player, weaponinfo[weapon].ammo, 5);
	else
	    P_GiveAmmo (player, weaponinfo[weapon].ammo, 2);
	player->pendingweapon = weapon;

	if (player == &players[consoleplayer])
	    S_StartSound (NULL, sfx_wpnup);
	return false;
    }
	
    if (weaponinfo[weapon].ammo != am_noammo)
    {
	// give one clip with a dropped weapon,
	// two clips with a found weapon
	if (dropped)
	    gaveammo = P_GiveAmmo (player, weaponinfo[weapon].ammo, 1);
	else
	    gaveammo = P_GiveAmmo (player, weaponinfo[weapon].ammo, 2);
    }
    else
	gaveammo = false;
	
    if (player->weaponowned[weapon])
	gaveweapon = false;
    else
    {
	gaveweapon = true;
	player->weaponowned[weapon] = true;
	player->pendingweapon = weapon;
    }
	
    return (gaveweapon || gaveammo);
}