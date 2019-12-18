#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {TYPE_3__ b; TYPE_1__ a; } ;
typedef  TYPE_7__ mline_t ;
struct TYPE_19__ {int flags; int special; TYPE_6__* frontsector; TYPE_5__* backsector; TYPE_4__* v2; TYPE_2__* v1; } ;
struct TYPE_18__ {scalar_t__* powers; } ;
struct TYPE_16__ {scalar_t__ floorheight; scalar_t__ ceilingheight; } ;
struct TYPE_15__ {scalar_t__ floorheight; scalar_t__ ceilingheight; } ;
struct TYPE_14__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_drawMline (TYPE_7__*,scalar_t__) ; 
 scalar_t__ CDWALLCOLORS ; 
 scalar_t__ FDWALLCOLORS ; 
 scalar_t__ GRAYS ; 
 int LINE_NEVERSEE ; 
 int ML_MAPPED ; 
 int ML_SECRET ; 
 scalar_t__ SECRETWALLCOLORS ; 
 scalar_t__ TSWALLCOLORS ; 
 scalar_t__ WALLCOLORS ; 
 int WALLRANGE ; 
 scalar_t__ cheating ; 
 scalar_t__ lightlev ; 
 TYPE_9__* lines ; 
 int numlines ; 
 TYPE_8__* plr ; 
 size_t pw_allmap ; 

void AM_drawWalls(void)
{
    int i;
    static mline_t l;

    for (i=0;i<numlines;i++)
    {
	l.a.x = lines[i].v1->x;
	l.a.y = lines[i].v1->y;
	l.b.x = lines[i].v2->x;
	l.b.y = lines[i].v2->y;
	if (cheating || (lines[i].flags & ML_MAPPED))
	{
	    if ((lines[i].flags & LINE_NEVERSEE) && !cheating)
		continue;
	    if (!lines[i].backsector)
	    {
		AM_drawMline(&l, WALLCOLORS+lightlev);
	    }
	    else
	    {
		if (lines[i].special == 39)
		{ // teleporters
		    AM_drawMline(&l, WALLCOLORS+WALLRANGE/2);
		}
		else if (lines[i].flags & ML_SECRET) // secret door
		{
		    if (cheating) AM_drawMline(&l, SECRETWALLCOLORS + lightlev);
		    else AM_drawMline(&l, WALLCOLORS+lightlev);
		}
		else if (lines[i].backsector->floorheight
			   != lines[i].frontsector->floorheight) {
		    AM_drawMline(&l, FDWALLCOLORS + lightlev); // floor level change
		}
		else if (lines[i].backsector->ceilingheight
			   != lines[i].frontsector->ceilingheight) {
		    AM_drawMline(&l, CDWALLCOLORS+lightlev); // ceiling level change
		}
		else if (cheating) {
		    AM_drawMline(&l, TSWALLCOLORS+lightlev);
		}
	    }
	}
	else if (plr->powers[pw_allmap])
	{
	    if (!(lines[i].flags & LINE_NEVERSEE)) AM_drawMline(&l, GRAYS+3);
	}
    }
}