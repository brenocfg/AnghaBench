#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  width; } ;
struct TYPE_9__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB ; 
 int MAXPLAYERS ; 
 int NG_SPACINGX ; 
 int NG_STATSX ; 
 int NG_STATSY ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DrawPatch (int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ WI_SPACINGY ; 
 int /*<<< orphan*/  WI_drawAnimatedBack () ; 
 int /*<<< orphan*/  WI_drawLF () ; 
 int /*<<< orphan*/  WI_drawNum (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WI_drawPercent (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WI_slamBackground () ; 
 int /*<<< orphan*/ * cnt_frags ; 
 int /*<<< orphan*/ * cnt_items ; 
 int /*<<< orphan*/ * cnt_kills ; 
 int /*<<< orphan*/ * cnt_secret ; 
 scalar_t__ dofrags ; 
 TYPE_1__* frags ; 
 TYPE_1__* items ; 
 TYPE_1__* kills ; 
 int me ; 
 TYPE_1__** p ; 
 TYPE_3__* percent ; 
 int /*<<< orphan*/ * playeringame ; 
 TYPE_1__* secret ; 
 TYPE_1__* star ; 

void WI_drawNetgameStats(void)
{
    int		i;
    int		x;
    int		y;
    int		pwidth = SHORT(percent->width);

    WI_slamBackground();
    
    // draw animated background
    WI_drawAnimatedBack(); 

    WI_drawLF();

    // draw stat titles (top line)
    V_DrawPatch(NG_STATSX+NG_SPACINGX-SHORT(kills->width),
		NG_STATSY, FB, kills);

    V_DrawPatch(NG_STATSX+2*NG_SPACINGX-SHORT(items->width),
		NG_STATSY, FB, items);

    V_DrawPatch(NG_STATSX+3*NG_SPACINGX-SHORT(secret->width),
		NG_STATSY, FB, secret);
    
    if (dofrags)
	V_DrawPatch(NG_STATSX+4*NG_SPACINGX-SHORT(frags->width),
		    NG_STATSY, FB, frags);

    // draw stats
    y = NG_STATSY + SHORT(kills->height);

    for (i=0 ; i<MAXPLAYERS ; i++)
    {
	if (!playeringame[i])
	    continue;

	x = NG_STATSX;
	V_DrawPatch(x-SHORT(p[i]->width), y, FB, p[i]);

	if (i == me)
	    V_DrawPatch(x-SHORT(p[i]->width), y, FB, star);

	x += NG_SPACINGX;
	WI_drawPercent(x-pwidth, y+10, cnt_kills[i]);	x += NG_SPACINGX;
	WI_drawPercent(x-pwidth, y+10, cnt_items[i]);	x += NG_SPACINGX;
	WI_drawPercent(x-pwidth, y+10, cnt_secret[i]);	x += NG_SPACINGX;

	if (dofrags)
	    WI_drawNum(x, y+10, cnt_frags[i], -1);

	y += WI_SPACINGY;
    }

}