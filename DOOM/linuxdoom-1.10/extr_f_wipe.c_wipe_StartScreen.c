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
 int /*<<< orphan*/ * screens ; 
 int /*<<< orphan*/  wipe_scr_start ; 

int
wipe_StartScreen
( int	x,
  int	y,
  int	width,
  int	height )
{
    wipe_scr_start = screens[2];
    I_ReadScreen(wipe_scr_start);
    return 0;
}