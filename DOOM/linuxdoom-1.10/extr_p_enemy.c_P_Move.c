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
struct TYPE_7__ {size_t movedir; int flags; scalar_t__ z; scalar_t__ floorz; TYPE_1__* info; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ mobj_t ;
typedef  int /*<<< orphan*/  line_t ;
typedef  scalar_t__ fixed_t ;
typedef  int boolean ;
struct TYPE_6__ {int speed; } ;

/* Variables and functions */
 size_t DI_NODIR ; 
 scalar_t__ FLOATSPEED ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int MF_FLOAT ; 
 int MF_INFLOAT ; 
 int P_TryMove (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ P_UseSpecialLine (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ floatok ; 
 size_t numspechit ; 
 int /*<<< orphan*/ ** spechit ; 
 scalar_t__ tmfloorz ; 
 int* xspeed ; 
 int* yspeed ; 

boolean P_Move (mobj_t*	actor)
{
    fixed_t	tryx;
    fixed_t	tryy;
    
    line_t*	ld;
    
    // warning: 'catch', 'throw', and 'try'
    // are all C++ reserved words
    boolean	try_ok;
    boolean	good;
		
    if (actor->movedir == DI_NODIR)
	return false;
		
    if ((unsigned)actor->movedir >= 8)
	I_Error ("Weird actor->movedir!");
		
    tryx = actor->x + actor->info->speed*xspeed[actor->movedir];
    tryy = actor->y + actor->info->speed*yspeed[actor->movedir];

    try_ok = P_TryMove (actor, tryx, tryy);

    if (!try_ok)
    {
	// open any specials
	if (actor->flags & MF_FLOAT && floatok)
	{
	    // must adjust height
	    if (actor->z < tmfloorz)
		actor->z += FLOATSPEED;
	    else
		actor->z -= FLOATSPEED;

	    actor->flags |= MF_INFLOAT;
	    return true;
	}
		
	if (!numspechit)
	    return false;
			
	actor->movedir = DI_NODIR;
	good = false;
	while (numspechit--)
	{
	    ld = spechit[numspechit];
	    // if the special is not a door
	    // that can be opened,
	    // return false
	    if (P_UseSpecialLine (actor, ld,0))
		good = true;
	}
	return good;
    }
    else
    {
	actor->flags &= ~MF_INFLOAT;
    }
	
	
    if (! (actor->flags & MF_FLOAT) )	
	actor->z = actor->floorz;
    return true; 
}