#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int epsd; int last; int next; int pnum; int maxkills; int maxitems; int maxsecret; int /*<<< orphan*/  plyr; } ;
typedef  TYPE_1__ wbstartstruct_t ;

/* Variables and functions */
 int MAXPLAYERS ; 
 int /*<<< orphan*/  RNGCHECK (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ acceleratestage ; 
 scalar_t__ bcnt ; 
 scalar_t__ cnt ; 
 scalar_t__ commercial ; 
 int firstrefresh ; 
 scalar_t__ gamemode ; 
 int me ; 
 int /*<<< orphan*/  plrs ; 
 scalar_t__ retail ; 
 TYPE_1__* wbs ; 

void WI_initVariables(wbstartstruct_t* wbstartstruct)
{

    wbs = wbstartstruct;

#ifdef RANGECHECKING
    if (gamemode != commercial)
    {
      if ( gamemode == retail )
	RNGCHECK(wbs->epsd, 0, 3);
      else
	RNGCHECK(wbs->epsd, 0, 2);
    }
    else
    {
	RNGCHECK(wbs->last, 0, 8);
	RNGCHECK(wbs->next, 0, 8);
    }
    RNGCHECK(wbs->pnum, 0, MAXPLAYERS);
    RNGCHECK(wbs->pnum, 0, MAXPLAYERS);
#endif

    acceleratestage = 0;
    cnt = bcnt = 0;
    firstrefresh = 1;
    me = wbs->pnum;
    plrs = wbs->plyr;

    if (!wbs->maxkills)
	wbs->maxkills = 1;

    if (!wbs->maxitems)
	wbs->maxitems = 1;

    if (!wbs->maxsecret)
	wbs->maxsecret = 1;

    if ( gamemode != retail )
      if (wbs->epsd > 2)
	wbs->epsd -= 3;
}