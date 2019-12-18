#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int integer; } ;
struct TYPE_3__ {scalar_t__ gametype; } ;

/* Variables and functions */
 float CG_DrawPowerups (float) ; 
 float CG_DrawScores (float) ; 
 float CG_DrawTeamOverlay (float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GT_TEAM ; 
 int ICON_SIZE ; 
 TYPE_2__ cg_drawTeamOverlay ; 
 TYPE_1__ cgs ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static void CG_DrawLowerRight( void ) {
	float	y;

	y = 480 - ICON_SIZE;

	if ( cgs.gametype >= GT_TEAM && cg_drawTeamOverlay.integer == 2 ) {
		y = CG_DrawTeamOverlay( y, qtrue, qfalse );
	} 

	y = CG_DrawScores( y );
	y = CG_DrawPowerups( y );
}