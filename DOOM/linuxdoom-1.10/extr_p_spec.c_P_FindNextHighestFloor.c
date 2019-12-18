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
struct TYPE_5__ {int linecount; scalar_t__ floorheight; int /*<<< orphan*/ ** lines; } ;
typedef  TYPE_1__ sector_t ;
typedef  int /*<<< orphan*/  line_t ;
typedef  scalar_t__ fixed_t ;

/* Variables and functions */
 int MAX_ADJOINING_SECTORS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* getNextSector (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 

fixed_t
P_FindNextHighestFloor
( sector_t*	sec,
  int		currentheight )
{
    int			i;
    int			h;
    int			min;
    line_t*		check;
    sector_t*		other;
    fixed_t		height = currentheight;

    
    fixed_t		heightlist[MAX_ADJOINING_SECTORS];		

    for (i=0, h=0 ;i < sec->linecount ; i++)
    {
	check = sec->lines[i];
	other = getNextSector(check,sec);

	if (!other)
	    continue;
	
	if (other->floorheight > height)
	    heightlist[h++] = other->floorheight;

	// Check for overflow. Exit.
	if ( h >= MAX_ADJOINING_SECTORS )
	{
	    fprintf( stderr,
		     "Sector with more than 20 adjoining sectors\n" );
	    break;
	}
    }
    
    // Find lowest height in list
    if (!h)
	return currentheight;
		
    min = heightlist[0];
    
    // Range checking? 
    for (i = 1;i < h;i++)
	if (heightlist[i] < min)
	    min = heightlist[i];
			
    return min;
}