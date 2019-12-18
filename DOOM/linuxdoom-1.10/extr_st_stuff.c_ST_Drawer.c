#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ST_diffDraw () ; 
 int /*<<< orphan*/  ST_doPaletteStuff () ; 
 int /*<<< orphan*/  ST_doRefresh () ; 
 scalar_t__ automapactive ; 
 int st_firsttime ; 
 int st_statusbaron ; 

void ST_Drawer (boolean fullscreen, boolean refresh)
{
  
    st_statusbaron = (!fullscreen) || automapactive;
    st_firsttime = st_firsttime || refresh;

    // Do red-/gold-shifts from damage/items
    ST_doPaletteStuff();

    // If just after ST_Start(), refresh all
    if (st_firsttime) ST_doRefresh();
    // Otherwise, update as little as possible
    else ST_diffDraw();

}