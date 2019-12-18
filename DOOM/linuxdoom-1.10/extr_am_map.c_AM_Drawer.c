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

/* Variables and functions */
 int /*<<< orphan*/  AM_clearFB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AM_drawCrosshair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AM_drawGrid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AM_drawMarks () ; 
 int /*<<< orphan*/  AM_drawPlayers () ; 
 int /*<<< orphan*/  AM_drawThings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AM_drawWalls () ; 
 int /*<<< orphan*/  BACKGROUND ; 
 int /*<<< orphan*/  GRIDCOLORS ; 
 int /*<<< orphan*/  THINGCOLORS ; 
 int /*<<< orphan*/  THINGRANGE ; 
 int /*<<< orphan*/  V_MarkRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHAIRCOLORS ; 
 int /*<<< orphan*/  automapactive ; 
 int cheating ; 
 int /*<<< orphan*/  f_h ; 
 int /*<<< orphan*/  f_w ; 
 int /*<<< orphan*/  f_x ; 
 int /*<<< orphan*/  f_y ; 
 scalar_t__ grid ; 

void AM_Drawer (void)
{
    if (!automapactive) return;

    AM_clearFB(BACKGROUND);
    if (grid)
	AM_drawGrid(GRIDCOLORS);
    AM_drawWalls();
    AM_drawPlayers();
    if (cheating==2)
	AM_drawThings(THINGCOLORS, THINGRANGE);
    AM_drawCrosshair(XHAIRCOLORS);

    AM_drawMarks();

    V_MarkRect(f_x, f_y, f_w, f_h);

}