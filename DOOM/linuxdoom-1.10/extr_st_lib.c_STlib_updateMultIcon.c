#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int oldinum; int* inum; int x; int y; TYPE_2__** p; scalar_t__* on; } ;
typedef  TYPE_1__ st_multicon_t ;
typedef  scalar_t__ boolean ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  topoffset; int /*<<< orphan*/  leftoffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG ; 
 int /*<<< orphan*/  FG ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 int ST_Y ; 
 int /*<<< orphan*/  V_CopyRect (int,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DrawPatch (int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )
{
    int			w;
    int			h;
    int			x;
    int			y;

    if (*mi->on
	&& (mi->oldinum != *mi->inum || refresh)
	&& (*mi->inum!=-1))
    {
	if (mi->oldinum != -1)
	{
	    x = mi->x - SHORT(mi->p[mi->oldinum]->leftoffset);
	    y = mi->y - SHORT(mi->p[mi->oldinum]->topoffset);
	    w = SHORT(mi->p[mi->oldinum]->width);
	    h = SHORT(mi->p[mi->oldinum]->height);

	    if (y - ST_Y < 0)
		I_Error("updateMultIcon: y - ST_Y < 0");

	    V_CopyRect(x, y-ST_Y, BG, w, h, x, y, FG);
	}
	V_DrawPatch(mi->x, mi->y, FG, mi->p[*mi->inum]);
	mi->oldinum = *mi->inum;
    }
}