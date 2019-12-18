#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tag; int linecount; int lightlevel; TYPE_2__** lines; } ;
typedef  TYPE_1__ sector_t ;
struct TYPE_9__ {scalar_t__ tag; } ;
typedef  TYPE_2__ line_t ;

/* Variables and functions */
 TYPE_1__* getNextSector (TYPE_2__*,TYPE_1__*) ; 
 int numsectors ; 
 TYPE_1__* sectors ; 

void
EV_LightTurnOn
( line_t*	line,
  int		bright )
{
    int		i;
    int		j;
    sector_t*	sector;
    sector_t*	temp;
    line_t*	templine;
	
    sector = sectors;
	
    for (i=0;i<numsectors;i++, sector++)
    {
	if (sector->tag == line->tag)
	{
	    // bright = 0 means to search
	    // for highest light level
	    // surrounding sector
	    if (!bright)
	    {
		for (j = 0;j < sector->linecount; j++)
		{
		    templine = sector->lines[j];
		    temp = getNextSector(templine,sector);

		    if (!temp)
			continue;

		    if (temp->lightlevel > bright)
			bright = temp->lightlevel;
		}
	    }
	    sector-> lightlevel = bright;
	}
    }
}