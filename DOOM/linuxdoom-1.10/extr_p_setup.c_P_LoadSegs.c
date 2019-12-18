#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int angle; int offset; scalar_t__ backsector; scalar_t__ frontsector; TYPE_4__* sidedef; TYPE_3__* linedef; int /*<<< orphan*/ * v2; int /*<<< orphan*/ * v1; } ;
typedef  TYPE_1__ seg_t ;
struct TYPE_10__ {int /*<<< orphan*/  side; int /*<<< orphan*/  linedef; int /*<<< orphan*/  offset; int /*<<< orphan*/  angle; int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; } ;
typedef  TYPE_2__ mapseg_t ;
struct TYPE_11__ {size_t* sidenum; int flags; } ;
typedef  TYPE_3__ line_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_12__ {scalar_t__ sector; } ;

/* Variables and functions */
 int ML_TWOSIDED ; 
 int /*<<< orphan*/  PU_LEVEL ; 
 int /*<<< orphan*/  PU_STATIC ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * W_CacheLumpNum (int,int /*<<< orphan*/ ) ; 
 int W_LumpLength (int) ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* lines ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int numsegs ; 
 TYPE_1__* segs ; 
 TYPE_4__* sides ; 
 int /*<<< orphan*/ * vertexes ; 

void P_LoadSegs (int lump)
{
    byte*		data;
    int			i;
    mapseg_t*		ml;
    seg_t*		li;
    line_t*		ldef;
    int			linedef;
    int			side;
	
    numsegs = W_LumpLength (lump) / sizeof(mapseg_t);
    segs = Z_Malloc (numsegs*sizeof(seg_t),PU_LEVEL,0);	
    memset (segs, 0, numsegs*sizeof(seg_t));
    data = W_CacheLumpNum (lump,PU_STATIC);
	
    ml = (mapseg_t *)data;
    li = segs;
    for (i=0 ; i<numsegs ; i++, li++, ml++)
    {
	li->v1 = &vertexes[SHORT(ml->v1)];
	li->v2 = &vertexes[SHORT(ml->v2)];
					
	li->angle = (SHORT(ml->angle))<<16;
	li->offset = (SHORT(ml->offset))<<16;
	linedef = SHORT(ml->linedef);
	ldef = &lines[linedef];
	li->linedef = ldef;
	side = SHORT(ml->side);
	li->sidedef = &sides[ldef->sidenum[side]];
	li->frontsector = sides[ldef->sidenum[side]].sector;
	if (ldef-> flags & ML_TWOSIDED)
	    li->backsector = sides[ldef->sidenum[side^1]].sector;
	else
	    li->backsector = 0;
    }
	
    Z_Free (data);
}