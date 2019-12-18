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
 int /*<<< orphan*/  AM_activateNewScale () ; 
 int /*<<< orphan*/  AM_maxOutWindowScale () ; 
 int /*<<< orphan*/  AM_minOutWindowScale () ; 
 int /*<<< orphan*/  FRACUNIT ; 
 int /*<<< orphan*/  FixedDiv (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FixedMul (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ max_scale_mtof ; 
 scalar_t__ min_scale_mtof ; 
 int /*<<< orphan*/  mtof_zoommul ; 
 int /*<<< orphan*/  scale_ftom ; 
 scalar_t__ scale_mtof ; 

void AM_changeWindowScale(void)
{

    // Change the scaling multipliers
    scale_mtof = FixedMul(scale_mtof, mtof_zoommul);
    scale_ftom = FixedDiv(FRACUNIT, scale_mtof);

    if (scale_mtof < min_scale_mtof)
	AM_minOutWindowScale();
    else if (scale_mtof > max_scale_mtof)
	AM_maxOutWindowScale();
    else
	AM_activateNewScale();
}