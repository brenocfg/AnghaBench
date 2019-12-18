#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean ;
typedef  scalar_t__ angle_t ;
struct TYPE_4__ {scalar_t__ health; scalar_t__* weaponowned; int cheats; scalar_t__* powers; scalar_t__ attackdown; scalar_t__ damagecount; TYPE_1__* mo; TYPE_1__* attacker; scalar_t__ bonuscount; } ;
struct TYPE_3__ {scalar_t__ angle; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ ANG180 ; 
 scalar_t__ ANG45 ; 
 int CF_GODMODE ; 
 int NUMWEAPONS ; 
 scalar_t__ R_PointToAngle2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ST_DEADFACE ; 
 int ST_EVILGRINCOUNT ; 
 scalar_t__ ST_EVILGRINOFFSET ; 
 scalar_t__ ST_GODFACE ; 
 scalar_t__ ST_MUCHPAIN ; 
 scalar_t__ ST_OUCHOFFSET ; 
 int ST_RAMPAGEDELAY ; 
 scalar_t__ ST_RAMPAGEOFFSET ; 
 int ST_STRAIGHTFACECOUNT ; 
 int ST_TURNCOUNT ; 
 scalar_t__ ST_TURNOFFSET ; 
 scalar_t__ ST_calcPainOffset () ; 
 scalar_t__* oldweaponsowned ; 
 TYPE_2__* plyr ; 
 size_t pw_invulnerability ; 
 int st_facecount ; 
 scalar_t__ st_faceindex ; 
 scalar_t__ st_oldhealth ; 
 int st_randomnumber ; 

void ST_updateFaceWidget(void)
{
    int		i;
    angle_t	badguyangle;
    angle_t	diffang;
    static int	lastattackdown = -1;
    static int	priority = 0;
    boolean	doevilgrin;

    if (priority < 10)
    {
	// dead
	if (!plyr->health)
	{
	    priority = 9;
	    st_faceindex = ST_DEADFACE;
	    st_facecount = 1;
	}
    }

    if (priority < 9)
    {
	if (plyr->bonuscount)
	{
	    // picking up bonus
	    doevilgrin = false;

	    for (i=0;i<NUMWEAPONS;i++)
	    {
		if (oldweaponsowned[i] != plyr->weaponowned[i])
		{
		    doevilgrin = true;
		    oldweaponsowned[i] = plyr->weaponowned[i];
		}
	    }
	    if (doevilgrin) 
	    {
		// evil grin if just picked up weapon
		priority = 8;
		st_facecount = ST_EVILGRINCOUNT;
		st_faceindex = ST_calcPainOffset() + ST_EVILGRINOFFSET;
	    }
	}

    }
  
    if (priority < 8)
    {
	if (plyr->damagecount
	    && plyr->attacker
	    && plyr->attacker != plyr->mo)
	{
	    // being attacked
	    priority = 7;
	    
	    if (plyr->health - st_oldhealth > ST_MUCHPAIN)
	    {
		st_facecount = ST_TURNCOUNT;
		st_faceindex = ST_calcPainOffset() + ST_OUCHOFFSET;
	    }
	    else
	    {
		badguyangle = R_PointToAngle2(plyr->mo->x,
					      plyr->mo->y,
					      plyr->attacker->x,
					      plyr->attacker->y);
		
		if (badguyangle > plyr->mo->angle)
		{
		    // whether right or left
		    diffang = badguyangle - plyr->mo->angle;
		    i = diffang > ANG180; 
		}
		else
		{
		    // whether left or right
		    diffang = plyr->mo->angle - badguyangle;
		    i = diffang <= ANG180; 
		} // confusing, aint it?

		
		st_facecount = ST_TURNCOUNT;
		st_faceindex = ST_calcPainOffset();
		
		if (diffang < ANG45)
		{
		    // head-on    
		    st_faceindex += ST_RAMPAGEOFFSET;
		}
		else if (i)
		{
		    // turn face right
		    st_faceindex += ST_TURNOFFSET;
		}
		else
		{
		    // turn face left
		    st_faceindex += ST_TURNOFFSET+1;
		}
	    }
	}
    }
  
    if (priority < 7)
    {
	// getting hurt because of your own damn stupidity
	if (plyr->damagecount)
	{
	    if (plyr->health - st_oldhealth > ST_MUCHPAIN)
	    {
		priority = 7;
		st_facecount = ST_TURNCOUNT;
		st_faceindex = ST_calcPainOffset() + ST_OUCHOFFSET;
	    }
	    else
	    {
		priority = 6;
		st_facecount = ST_TURNCOUNT;
		st_faceindex = ST_calcPainOffset() + ST_RAMPAGEOFFSET;
	    }

	}

    }
  
    if (priority < 6)
    {
	// rapid firing
	if (plyr->attackdown)
	{
	    if (lastattackdown==-1)
		lastattackdown = ST_RAMPAGEDELAY;
	    else if (!--lastattackdown)
	    {
		priority = 5;
		st_faceindex = ST_calcPainOffset() + ST_RAMPAGEOFFSET;
		st_facecount = 1;
		lastattackdown = 1;
	    }
	}
	else
	    lastattackdown = -1;

    }
  
    if (priority < 5)
    {
	// invulnerability
	if ((plyr->cheats & CF_GODMODE)
	    || plyr->powers[pw_invulnerability])
	{
	    priority = 4;

	    st_faceindex = ST_GODFACE;
	    st_facecount = 1;

	}

    }

    // look left or look right if the facecount has timed out
    if (!st_facecount)
    {
	st_faceindex = ST_calcPainOffset() + (st_randomnumber % 3);
	st_facecount = ST_STRAIGHTFACECOUNT;
	priority = 0;
    }

    st_facecount--;

}