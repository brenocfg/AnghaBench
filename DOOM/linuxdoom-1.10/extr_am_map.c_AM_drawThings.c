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
struct TYPE_3__ {struct TYPE_3__* snext; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  angle; } ;
typedef  TYPE_1__ mobj_t ;
struct TYPE_4__ {TYPE_1__* thinglist; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_drawLineCharacter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FRACBITS ; 
 int /*<<< orphan*/  NUMTHINTRIANGLEGUYLINES ; 
 scalar_t__ lightlev ; 
 int numsectors ; 
 TYPE_2__* sectors ; 
 int /*<<< orphan*/  thintriangle_guy ; 

void
AM_drawThings
( int	colors,
  int 	colorrange)
{
    int		i;
    mobj_t*	t;

    for (i=0;i<numsectors;i++)
    {
	t = sectors[i].thinglist;
	while (t)
	{
	    AM_drawLineCharacter
		(thintriangle_guy, NUMTHINTRIANGLEGUYLINES,
		 16<<FRACBITS, t->angle, colors+lightlev, t->x, t->y);
	    t = t->snext;
	}
    }
}