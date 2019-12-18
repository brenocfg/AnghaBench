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
struct TYPE_4__ {int flags; int planenum; scalar_t__ texinfo; scalar_t__ surf; int /*<<< orphan*/  contents; int /*<<< orphan*/ * winding; int /*<<< orphan*/ * original; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_5__ {int numsides; int /*<<< orphan*/  contents; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MAX_MAPFILE_BRUSHSIDES ; 
 int SFL_BEVEL ; 
 int SFL_VISIBLE ; 
 scalar_t__ nummapbrushsides ; 

void AAS_AddMapBrushSide(mapbrush_t *brush, int planenum)
{
	side_t *side;
	//
	if (nummapbrushsides >= MAX_MAPFILE_BRUSHSIDES)
		Error ("MAX_MAPFILE_BRUSHSIDES");
	//
	side = brush->original_sides + brush->numsides;
	side->original = NULL;
	side->winding = NULL;
	side->contents = brush->contents;
	side->flags &= ~(SFL_BEVEL|SFL_VISIBLE);
	side->surf = 0;
	side->planenum = planenum;
	side->texinfo = 0;
	//
	nummapbrushsides++;
	brush->numsides++;
}