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
 int /*<<< orphan*/  I_ReadScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_DrawBlock (int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * screens ; 
 int /*<<< orphan*/  wipe_scr_end ; 
 int /*<<< orphan*/  wipe_scr_start ; 

int
wipe_EndScreen
( int	x,
  int	y,
  int	width,
  int	height )
{
    wipe_scr_end = screens[3];
    I_ReadScreen(wipe_scr_end);
    V_DrawBlock(x, y, 0, width, height, wipe_scr_start); // restore start scr.
    return 0;
}