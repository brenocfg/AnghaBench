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
typedef  int /*<<< orphan*/  GTIA_pm_scanline ;

/* Variables and functions */
 int /*<<< orphan*/  GTIA_M0PL ; 
 int /*<<< orphan*/  GTIA_M1PL ; 
 int /*<<< orphan*/  GTIA_M2PL ; 
 int /*<<< orphan*/  GTIA_M3PL ; 
 int /*<<< orphan*/  GTIA_P1PL ; 
 int /*<<< orphan*/  GTIA_P2PL ; 
 int /*<<< orphan*/  GTIA_P3PL ; 
 int /*<<< orphan*/  M0PL_T ; 
 int /*<<< orphan*/  M1PL_T ; 
 int /*<<< orphan*/  M2PL_T ; 
 int /*<<< orphan*/  M3PL_T ; 
 int /*<<< orphan*/  P1PL_T ; 
 int /*<<< orphan*/  P2PL_T ; 
 int /*<<< orphan*/  P3PL_T ; 
 scalar_t__ collision_curpos ; 
 int /*<<< orphan*/  generate_partial_pmpl_colls (scalar_t__,int) ; 
 scalar_t__ hitclr_pos ; 

void GTIA_UpdatePmplColls(void)
{
	if (hitclr_pos != 0){
		generate_partial_pmpl_colls(hitclr_pos,
				sizeof(GTIA_pm_scanline) / sizeof(GTIA_pm_scanline[0]) - 1);
/* If hitclr was written to, then only part of GTIA_pm_scanline should be used
 * for collisions */

	}
	else {
/* otherwise the whole of pm_scaline can be used for collisions.  This will
 * update the collision registers based on the generated collisions for the
 * current line */
		GTIA_P1PL |= P1PL_T;
		GTIA_P2PL |= P2PL_T;
		GTIA_P3PL |= P3PL_T;
		GTIA_M0PL |= M0PL_T;
		GTIA_M1PL |= M1PL_T;
		GTIA_M2PL |= M2PL_T;
		GTIA_M3PL |= M3PL_T;
	}
	collision_curpos = 0;
	hitclr_pos = 0;
}