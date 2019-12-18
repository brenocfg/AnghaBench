#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ specialdata; } ;
typedef  TYPE_1__ sector_t ;
typedef  int /*<<< orphan*/  line_t ;

/* Variables and functions */
 int P_FindSectorFromLineTag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  P_SpawnStrobeFlash (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOWDARK ; 
 TYPE_1__* sectors ; 

void EV_StartLightStrobing(line_t*	line)
{
    int		secnum;
    sector_t*	sec;
	
    secnum = -1;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
	sec = &sectors[secnum];
	if (sec->specialdata)
	    continue;
	
	P_SpawnStrobeFlash (sec,SLOWDARK, 0);
    }
}