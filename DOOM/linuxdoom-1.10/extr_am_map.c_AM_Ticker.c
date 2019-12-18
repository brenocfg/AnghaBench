#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_changeWindowLoc () ; 
 int /*<<< orphan*/  AM_changeWindowScale () ; 
 int /*<<< orphan*/  AM_doFollowPlayer () ; 
 scalar_t__ FRACUNIT ; 
 int /*<<< orphan*/  amclock ; 
 int /*<<< orphan*/  automapactive ; 
 scalar_t__ followplayer ; 
 scalar_t__ ftom_zoommul ; 
 TYPE_1__ m_paninc ; 

void AM_Ticker (void)
{

    if (!automapactive)
	return;

    amclock++;

    if (followplayer)
	AM_doFollowPlayer();

    // Change the zoom if necessary
    if (ftom_zoommul != FRACUNIT)
	AM_changeWindowScale();

    // Change x,y location
    if (m_paninc.x || m_paninc.y)
	AM_changeWindowLoc();

    // Update light level
    // AM_updateLightLev();

}