#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ height; int picnum; int lightlevel; int maxx; int /*<<< orphan*/  top; int /*<<< orphan*/  minx; } ;
typedef  TYPE_1__ visplane_t ;
typedef  scalar_t__ fixed_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*) ; 
 int MAXVISPLANES ; 
 int /*<<< orphan*/  SCREENWIDTH ; 
 TYPE_1__* lastvisplane ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int skyflatnum ; 
 TYPE_1__* visplanes ; 

visplane_t*
R_FindPlane
( fixed_t	height,
  int		picnum,
  int		lightlevel )
{
    visplane_t*	check;
	
    if (picnum == skyflatnum)
    {
	height = 0;			// all skys map together
	lightlevel = 0;
    }
	
    for (check=visplanes; check<lastvisplane; check++)
    {
	if (height == check->height
	    && picnum == check->picnum
	    && lightlevel == check->lightlevel)
	{
	    break;
	}
    }
    
			
    if (check < lastvisplane)
	return check;
		
    if (lastvisplane - visplanes == MAXVISPLANES)
	I_Error ("R_FindPlane: no more visplanes");
		
    lastvisplane++;

    check->height = height;
    check->picnum = picnum;
    check->lightlevel = lightlevel;
    check->minx = SCREENWIDTH;
    check->maxx = -1;
    
    memset (check->top,0xff,sizeof(check->top));
		
    return check;
}