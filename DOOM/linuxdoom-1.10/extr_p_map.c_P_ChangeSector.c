#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* blockbox; } ;
typedef  TYPE_1__ sector_t ;
typedef  int boolean ;

/* Variables and functions */
 size_t BOXBOTTOM ; 
 size_t BOXLEFT ; 
 size_t BOXRIGHT ; 
 size_t BOXTOP ; 
 int /*<<< orphan*/  PIT_ChangeSector ; 
 int /*<<< orphan*/  P_BlockThingsIterator (int,int,int /*<<< orphan*/ ) ; 
 int crushchange ; 
 int nofit ; 

boolean
P_ChangeSector
( sector_t*	sector,
  boolean	crunch )
{
    int		x;
    int		y;
	
    nofit = false;
    crushchange = crunch;
	
    // re-check heights for all things near the moving sector
    for (x=sector->blockbox[BOXLEFT] ; x<= sector->blockbox[BOXRIGHT] ; x++)
	for (y=sector->blockbox[BOXBOTTOM];y<= sector->blockbox[BOXTOP] ; y++)
	    P_BlockThingsIterator (x, y, PIT_ChangeSector);
	
	
    return nofit;
}