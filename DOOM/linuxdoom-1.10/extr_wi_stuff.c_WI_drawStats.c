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
struct TYPE_4__ {int /*<<< orphan*/  height; } ;
struct TYPE_3__ {int epsd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB ; 
 int SCREENWIDTH ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ SP_STATSX ; 
 scalar_t__ SP_STATSY ; 
 scalar_t__ SP_TIMEX ; 
 scalar_t__ SP_TIMEY ; 
 int /*<<< orphan*/  V_DrawPatch (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WI_drawAnimatedBack () ; 
 int /*<<< orphan*/  WI_drawLF () ; 
 int /*<<< orphan*/  WI_drawPercent (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WI_drawTime (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WI_slamBackground () ; 
 int /*<<< orphan*/ * cnt_items ; 
 int /*<<< orphan*/ * cnt_kills ; 
 int /*<<< orphan*/  cnt_par ; 
 int /*<<< orphan*/ * cnt_secret ; 
 int /*<<< orphan*/  cnt_time ; 
 int /*<<< orphan*/  items ; 
 int /*<<< orphan*/  kills ; 
 TYPE_2__** num ; 
 int /*<<< orphan*/  par ; 
 int /*<<< orphan*/  sp_secret ; 
 int /*<<< orphan*/  time ; 
 TYPE_1__* wbs ; 

void WI_drawStats(void)
{
    // line height
    int lh;	

    lh = (3*SHORT(num[0]->height))/2;

    WI_slamBackground();

    // draw animated background
    WI_drawAnimatedBack();
    
    WI_drawLF();

    V_DrawPatch(SP_STATSX, SP_STATSY, FB, kills);
    WI_drawPercent(SCREENWIDTH - SP_STATSX, SP_STATSY, cnt_kills[0]);

    V_DrawPatch(SP_STATSX, SP_STATSY+lh, FB, items);
    WI_drawPercent(SCREENWIDTH - SP_STATSX, SP_STATSY+lh, cnt_items[0]);

    V_DrawPatch(SP_STATSX, SP_STATSY+2*lh, FB, sp_secret);
    WI_drawPercent(SCREENWIDTH - SP_STATSX, SP_STATSY+2*lh, cnt_secret[0]);

    V_DrawPatch(SP_TIMEX, SP_TIMEY, FB, time);
    WI_drawTime(SCREENWIDTH/2 - SP_TIMEX, SP_TIMEY, cnt_time);

    if (wbs->epsd < 3)
    {
	V_DrawPatch(SCREENWIDTH/2 + SP_TIMEX, SP_TIMEY, FB, par);
	WI_drawTime(SCREENWIDTH - SP_TIMEX, SP_TIMEY, cnt_par);
    }

}