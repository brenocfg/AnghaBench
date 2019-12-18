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
struct TYPE_4__ {int nanims; int /*<<< orphan*/ * p; } ;
struct TYPE_3__ {int epsd; } ;

/* Variables and functions */
 int MAXPLAYERS ; 
 int* NUMANIMS ; 
 int NUMCMAPS ; 
 int NUMMAPS ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  Z_ChangeTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ *) ; 
 TYPE_2__** anims ; 
 int /*<<< orphan*/ * bp ; 
 int /*<<< orphan*/  colon ; 
 scalar_t__ commercial ; 
 int /*<<< orphan*/  entering ; 
 int /*<<< orphan*/  finished ; 
 int /*<<< orphan*/  frags ; 
 scalar_t__ gamemode ; 
 int /*<<< orphan*/  items ; 
 int /*<<< orphan*/  killers ; 
 int /*<<< orphan*/  kills ; 
 int /*<<< orphan*/ * lnames ; 
 int /*<<< orphan*/ * num ; 
 int /*<<< orphan*/ * p ; 
 int /*<<< orphan*/  par ; 
 int /*<<< orphan*/  percent ; 
 int /*<<< orphan*/  secret ; 
 int /*<<< orphan*/  sp_secret ; 
 int /*<<< orphan*/  splat ; 
 int /*<<< orphan*/  sucks ; 
 int /*<<< orphan*/  time ; 
 int /*<<< orphan*/  total ; 
 int /*<<< orphan*/  victims ; 
 TYPE_1__* wbs ; 
 int /*<<< orphan*/  wiminus ; 
 int /*<<< orphan*/ * yah ; 

void WI_unloadData(void)
{
    int		i;
    int		j;

    Z_ChangeTag(wiminus, PU_CACHE);

    for (i=0 ; i<10 ; i++)
	Z_ChangeTag(num[i], PU_CACHE);
    
    if (gamemode == commercial)
    {
  	for (i=0 ; i<NUMCMAPS ; i++)
	    Z_ChangeTag(lnames[i], PU_CACHE);
    }
    else
    {
	Z_ChangeTag(yah[0], PU_CACHE);
	Z_ChangeTag(yah[1], PU_CACHE);

	Z_ChangeTag(splat, PU_CACHE);

	for (i=0 ; i<NUMMAPS ; i++)
	    Z_ChangeTag(lnames[i], PU_CACHE);
	
	if (wbs->epsd < 3)
	{
	    for (j=0;j<NUMANIMS[wbs->epsd];j++)
	    {
		if (wbs->epsd != 1 || j != 8)
		    for (i=0;i<anims[wbs->epsd][j].nanims;i++)
			Z_ChangeTag(anims[wbs->epsd][j].p[i], PU_CACHE);
	    }
	}
    }
    
    Z_Free(lnames);

    Z_ChangeTag(percent, PU_CACHE);
    Z_ChangeTag(colon, PU_CACHE);
    Z_ChangeTag(finished, PU_CACHE);
    Z_ChangeTag(entering, PU_CACHE);
    Z_ChangeTag(kills, PU_CACHE);
    Z_ChangeTag(secret, PU_CACHE);
    Z_ChangeTag(sp_secret, PU_CACHE);
    Z_ChangeTag(items, PU_CACHE);
    Z_ChangeTag(frags, PU_CACHE);
    Z_ChangeTag(time, PU_CACHE);
    Z_ChangeTag(sucks, PU_CACHE);
    Z_ChangeTag(par, PU_CACHE);

    Z_ChangeTag(victims, PU_CACHE);
    Z_ChangeTag(killers, PU_CACHE);
    Z_ChangeTag(total, PU_CACHE);
    //  Z_ChangeTag(star, PU_CACHE);
    //  Z_ChangeTag(bstar, PU_CACHE);
    
    for (i=0 ; i<MAXPLAYERS ; i++)
	Z_ChangeTag(p[i], PU_CACHE);

    for (i=0 ; i<MAXPLAYERS ; i++)
	Z_ChangeTag(bp[i], PU_CACHE);
}