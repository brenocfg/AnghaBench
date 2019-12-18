#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t weapontype_t ;
struct TYPE_16__ {int forwardmove; int buttons; scalar_t__ sidemove; scalar_t__ angleturn; } ;
typedef  TYPE_4__ ticcmd_t ;
struct TYPE_17__ {int cheats; scalar_t__ playerstate; size_t readyweapon; int* powers; size_t pendingweapon; int usedown; int fixedcolormap; scalar_t__ bonuscount; scalar_t__ damagecount; TYPE_3__* mo; scalar_t__* weaponowned; TYPE_4__ cmd; } ;
typedef  TYPE_5__ player_t ;
struct TYPE_15__ {int flags; TYPE_2__* subsector; scalar_t__ reactiontime; } ;
struct TYPE_14__ {TYPE_1__* sector; } ;
struct TYPE_13__ {scalar_t__ special; } ;

/* Variables and functions */
 int BT_CHANGE ; 
 int BT_SPECIAL ; 
 int BT_USE ; 
 size_t BT_WEAPONMASK ; 
 size_t BT_WEAPONSHIFT ; 
 int CF_NOCLIP ; 
 int INVERSECOLORMAP ; 
 int MF_JUSTATTACKED ; 
 int MF_NOCLIP ; 
 int MF_SHADOW ; 
 scalar_t__ PST_DEAD ; 
 int /*<<< orphan*/  P_CalcHeight (TYPE_5__*) ; 
 int /*<<< orphan*/  P_DeathThink (TYPE_5__*) ; 
 int /*<<< orphan*/  P_MovePlayer (TYPE_5__*) ; 
 int /*<<< orphan*/  P_MovePsprites (TYPE_5__*) ; 
 int /*<<< orphan*/  P_PlayerInSpecialSector (TYPE_5__*) ; 
 int /*<<< orphan*/  P_UseLines (TYPE_5__*) ; 
 scalar_t__ commercial ; 
 scalar_t__ gamemode ; 
 size_t pw_infrared ; 
 size_t pw_invisibility ; 
 size_t pw_invulnerability ; 
 size_t pw_ironfeet ; 
 size_t pw_strength ; 
 scalar_t__ shareware ; 
 size_t wp_bfg ; 
 size_t wp_chainsaw ; 
 size_t wp_fist ; 
 size_t wp_plasma ; 
 size_t wp_shotgun ; 
 size_t wp_supershotgun ; 

void P_PlayerThink (player_t* player)
{
    ticcmd_t*		cmd;
    weapontype_t	newweapon;
	
    // fixme: do this in the cheat code
    if (player->cheats & CF_NOCLIP)
	player->mo->flags |= MF_NOCLIP;
    else
	player->mo->flags &= ~MF_NOCLIP;
    
    // chain saw run forward
    cmd = &player->cmd;
    if (player->mo->flags & MF_JUSTATTACKED)
    {
	cmd->angleturn = 0;
	cmd->forwardmove = 0xc800/512;
	cmd->sidemove = 0;
	player->mo->flags &= ~MF_JUSTATTACKED;
    }
			
	
    if (player->playerstate == PST_DEAD)
    {
	P_DeathThink (player);
	return;
    }
    
    // Move around.
    // Reactiontime is used to prevent movement
    //  for a bit after a teleport.
    if (player->mo->reactiontime)
	player->mo->reactiontime--;
    else
	P_MovePlayer (player);
    
    P_CalcHeight (player);

    if (player->mo->subsector->sector->special)
	P_PlayerInSpecialSector (player);
    
    // Check for weapon change.

    // A special event has no other buttons.
    if (cmd->buttons & BT_SPECIAL)
	cmd->buttons = 0;			
		
    if (cmd->buttons & BT_CHANGE)
    {
	// The actual changing of the weapon is done
	//  when the weapon psprite can do it
	//  (read: not in the middle of an attack).
	newweapon = (cmd->buttons&BT_WEAPONMASK)>>BT_WEAPONSHIFT;
	
	if (newweapon == wp_fist
	    && player->weaponowned[wp_chainsaw]
	    && !(player->readyweapon == wp_chainsaw
		 && player->powers[pw_strength]))
	{
	    newweapon = wp_chainsaw;
	}
	
	if ( (gamemode == commercial)
	    && newweapon == wp_shotgun 
	    && player->weaponowned[wp_supershotgun]
	    && player->readyweapon != wp_supershotgun)
	{
	    newweapon = wp_supershotgun;
	}
	

	if (player->weaponowned[newweapon]
	    && newweapon != player->readyweapon)
	{
	    // Do not go to plasma or BFG in shareware,
	    //  even if cheated.
	    if ((newweapon != wp_plasma
		 && newweapon != wp_bfg)
		|| (gamemode != shareware) )
	    {
		player->pendingweapon = newweapon;
	    }
	}
    }
    
    // check for use
    if (cmd->buttons & BT_USE)
    {
	if (!player->usedown)
	{
	    P_UseLines (player);
	    player->usedown = true;
	}
    }
    else
	player->usedown = false;
    
    // cycle psprites
    P_MovePsprites (player);
    
    // Counters, time dependend power ups.

    // Strength counts up to diminish fade.
    if (player->powers[pw_strength])
	player->powers[pw_strength]++;	
		
    if (player->powers[pw_invulnerability])
	player->powers[pw_invulnerability]--;

    if (player->powers[pw_invisibility])
	if (! --player->powers[pw_invisibility] )
	    player->mo->flags &= ~MF_SHADOW;
			
    if (player->powers[pw_infrared])
	player->powers[pw_infrared]--;
		
    if (player->powers[pw_ironfeet])
	player->powers[pw_ironfeet]--;
		
    if (player->damagecount)
	player->damagecount--;
		
    if (player->bonuscount)
	player->bonuscount--;

    
    // Handling colormaps.
    if (player->powers[pw_invulnerability])
    {
	if (player->powers[pw_invulnerability] > 4*32
	    || (player->powers[pw_invulnerability]&8) )
	    player->fixedcolormap = INVERSECOLORMAP;
	else
	    player->fixedcolormap = 0;
    }
    else if (player->powers[pw_infrared])	
    {
	if (player->powers[pw_infrared] > 4*32
	    || (player->powers[pw_infrared]&8) )
	{
	    // almost full bright
	    player->fixedcolormap = 1;
	}
	else
	    player->fixedcolormap = 0;
    }
    else
	player->fixedcolormap = 0;
}