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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wipe_scr ; 
 int /*<<< orphan*/  wipe_scr_start ; 

int
wipe_initColorXForm
( int	width,
  int	height,
  int	ticks )
{
    memcpy(wipe_scr, wipe_scr_start, width*height);
    return 0;
}