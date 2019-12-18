#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int slopetype; int /*<<< orphan*/  dy; TYPE_1__* v1; int /*<<< orphan*/  dx; } ;
typedef  TYPE_2__ line_t ;
typedef  int /*<<< orphan*/  fixed_t ;
struct TYPE_5__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 size_t BOXBOTTOM ; 
 size_t BOXLEFT ; 
 size_t BOXRIGHT ; 
 size_t BOXTOP ; 
 int P_PointOnLineSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
#define  ST_HORIZONTAL 131 
#define  ST_NEGATIVE 130 
#define  ST_POSITIVE 129 
#define  ST_VERTICAL 128 

int
P_BoxOnLineSide
( fixed_t*	tmbox,
  line_t*	ld )
{
    int		p1;
    int		p2;
	
    switch (ld->slopetype)
    {
      case ST_HORIZONTAL:
	p1 = tmbox[BOXTOP] > ld->v1->y;
	p2 = tmbox[BOXBOTTOM] > ld->v1->y;
	if (ld->dx < 0)
	{
	    p1 ^= 1;
	    p2 ^= 1;
	}
	break;
	
      case ST_VERTICAL:
	p1 = tmbox[BOXRIGHT] < ld->v1->x;
	p2 = tmbox[BOXLEFT] < ld->v1->x;
	if (ld->dy < 0)
	{
	    p1 ^= 1;
	    p2 ^= 1;
	}
	break;
	
      case ST_POSITIVE:
	p1 = P_PointOnLineSide (tmbox[BOXLEFT], tmbox[BOXTOP], ld);
	p2 = P_PointOnLineSide (tmbox[BOXRIGHT], tmbox[BOXBOTTOM], ld);
	break;
	
      case ST_NEGATIVE:
	p1 = P_PointOnLineSide (tmbox[BOXRIGHT], tmbox[BOXTOP], ld);
	p2 = P_PointOnLineSide (tmbox[BOXLEFT], tmbox[BOXBOTTOM], ld);
	break;
    }

    if (p1 == p2)
	return p1;
    return -1;
}