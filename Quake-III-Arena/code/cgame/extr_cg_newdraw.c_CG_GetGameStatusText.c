#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* teamScores; TYPE_2__* snap; } ;
struct TYPE_7__ {scalar_t__ gametype; } ;
struct TYPE_5__ {scalar_t__* persistant; } ;
struct TYPE_6__ {TYPE_1__ ps; } ;

/* Variables and functions */
 scalar_t__ CG_PlaceString (scalar_t__) ; 
 scalar_t__ GT_TEAM ; 
 size_t PERS_RANK ; 
 size_t PERS_SCORE ; 
 size_t PERS_TEAM ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_4__ cg ; 
 TYPE_3__ cgs ; 
 char* va (char*,scalar_t__,...) ; 

const char *CG_GetGameStatusText() {
	const char *s = "";
	if ( cgs.gametype < GT_TEAM) {
		if (cg.snap->ps.persistant[PERS_TEAM] != TEAM_SPECTATOR ) {
			s = va("%s place with %i",CG_PlaceString( cg.snap->ps.persistant[PERS_RANK] + 1 ),cg.snap->ps.persistant[PERS_SCORE] );
		}
	} else {
		if ( cg.teamScores[0] == cg.teamScores[1] ) {
			s = va("Teams are tied at %i", cg.teamScores[0] );
		} else if ( cg.teamScores[0] >= cg.teamScores[1] ) {
			s = va("Red leads Blue, %i to %i", cg.teamScores[0], cg.teamScores[1] );
		} else {
			s = va("Blue leads Red, %i to %i", cg.teamScores[1], cg.teamScores[0] );
		}
	}
	return s;
}