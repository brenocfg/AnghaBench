#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int epsd; int last; int next; scalar_t__ didsecret; } ;

/* Variables and functions */
 int /*<<< orphan*/  WI_drawAnimatedBack () ; 
 int /*<<< orphan*/  WI_drawEL () ; 
 int /*<<< orphan*/  WI_drawOnLnode (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WI_slamBackground () ; 
 scalar_t__ commercial ; 
 scalar_t__ gamemode ; 
 scalar_t__ snl_pointeron ; 
 int /*<<< orphan*/  splat ; 
 TYPE_1__* wbs ; 
 int /*<<< orphan*/ * yah ; 

void WI_drawShowNextLoc(void)
{

    int		i;
    int		last;

    WI_slamBackground();

    // draw animated background
    WI_drawAnimatedBack(); 

    if ( gamemode != commercial)
    {
  	if (wbs->epsd > 2)
	{
	    WI_drawEL();
	    return;
	}
	
	last = (wbs->last == 8) ? wbs->next - 1 : wbs->last;

	// draw a splat on taken cities.
	for (i=0 ; i<=last ; i++)
	    WI_drawOnLnode(i, &splat);

	// splat the secret level?
	if (wbs->didsecret)
	    WI_drawOnLnode(8, &splat);

	// draw flashing ptr
	if (snl_pointeron)
	    WI_drawOnLnode(wbs->next, yah); 
    }

    // draws which level you are entering..
    if ( (gamemode != commercial)
	 || wbs->next != 30)
	WI_drawEL();  

}