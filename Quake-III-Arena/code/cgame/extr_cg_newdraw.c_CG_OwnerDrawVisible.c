#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_10__ {TYPE_2__* snap; } ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_8__ {scalar_t__ redflag; scalar_t__ flagStatus; scalar_t__ blueflag; scalar_t__ gametype; } ;
struct TYPE_6__ {int* stats; scalar_t__* powerups; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int CG_OtherTeamHasFlag () ; 
 int CG_SHOW_ANYNONTEAMGAME ; 
 int CG_SHOW_ANYTEAMGAME ; 
 int CG_SHOW_BLUE_TEAM_HAS_REDFLAG ; 
 int CG_SHOW_CTF ; 
 int CG_SHOW_DURINGINCOMINGVOICE ; 
 int CG_SHOW_HARVESTER ; 
 int CG_SHOW_HEALTHCRITICAL ; 
 int CG_SHOW_HEALTHOK ; 
 int CG_SHOW_IF_PLAYER_HAS_FLAG ; 
 int CG_SHOW_NOTEAMINFO ; 
 int CG_SHOW_OBELISK ; 
 int CG_SHOW_ONEFLAG ; 
 int CG_SHOW_OTHERTEAMHASFLAG ; 
 int CG_SHOW_RED_TEAM_HAS_BLUEFLAG ; 
 int CG_SHOW_SINGLEPLAYER ; 
 int CG_SHOW_TEAMINFO ; 
 int CG_SHOW_TOURNAMENT ; 
 int CG_SHOW_YOURTEAMHASENEMYFLAG ; 
 int CG_YourTeamHasFlag () ; 
 scalar_t__ FLAG_TAKEN ; 
 scalar_t__ FLAG_TAKEN_BLUE ; 
 scalar_t__ FLAG_TAKEN_RED ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ GT_OBELISK ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 scalar_t__ GT_TEAM ; 
 scalar_t__ GT_TOURNAMENT ; 
 size_t PW_BLUEFLAG ; 
 size_t PW_NEUTRALFLAG ; 
 size_t PW_REDFLAG ; 
 size_t STAT_HEALTH ; 
 TYPE_5__ cg ; 
 TYPE_4__ cg_currentSelectedPlayer ; 
 TYPE_3__ cgs ; 
 scalar_t__ numSortedTeamPlayers ; 
 int qfalse ; 
 int qtrue ; 

qboolean CG_OwnerDrawVisible(int flags) {

	if (flags & CG_SHOW_TEAMINFO) {
		return (cg_currentSelectedPlayer.integer == numSortedTeamPlayers);
	}

	if (flags & CG_SHOW_NOTEAMINFO) {
		return !(cg_currentSelectedPlayer.integer == numSortedTeamPlayers);
	}

	if (flags & CG_SHOW_OTHERTEAMHASFLAG) {
		return CG_OtherTeamHasFlag();
	}

	if (flags & CG_SHOW_YOURTEAMHASENEMYFLAG) {
		return CG_YourTeamHasFlag();
	}

	if (flags & (CG_SHOW_BLUE_TEAM_HAS_REDFLAG | CG_SHOW_RED_TEAM_HAS_BLUEFLAG)) {
		if (flags & CG_SHOW_BLUE_TEAM_HAS_REDFLAG && (cgs.redflag == FLAG_TAKEN || cgs.flagStatus == FLAG_TAKEN_RED)) {
			return qtrue;
		} else if (flags & CG_SHOW_RED_TEAM_HAS_BLUEFLAG && (cgs.blueflag == FLAG_TAKEN || cgs.flagStatus == FLAG_TAKEN_BLUE)) {
			return qtrue;
		}
		return qfalse;
	}

	if (flags & CG_SHOW_ANYTEAMGAME) {
		if( cgs.gametype >= GT_TEAM) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_ANYNONTEAMGAME) {
		if( cgs.gametype < GT_TEAM) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_HARVESTER) {
		if( cgs.gametype == GT_HARVESTER ) {
			return qtrue;
    } else {
      return qfalse;
    }
	}

	if (flags & CG_SHOW_ONEFLAG) {
		if( cgs.gametype == GT_1FCTF ) {
			return qtrue;
    } else {
      return qfalse;
    }
	}

	if (flags & CG_SHOW_CTF) {
		if( cgs.gametype == GT_CTF ) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_OBELISK) {
		if( cgs.gametype == GT_OBELISK ) {
			return qtrue;
    } else {
      return qfalse;
    }
	}

	if (flags & CG_SHOW_HEALTHCRITICAL) {
		if (cg.snap->ps.stats[STAT_HEALTH] < 25) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_HEALTHOK) {
		if (cg.snap->ps.stats[STAT_HEALTH] >= 25) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_SINGLEPLAYER) {
		if( cgs.gametype == GT_SINGLE_PLAYER ) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_TOURNAMENT) {
		if( cgs.gametype == GT_TOURNAMENT ) {
			return qtrue;
		}
	}

	if (flags & CG_SHOW_DURINGINCOMINGVOICE) {
	}

	if (flags & CG_SHOW_IF_PLAYER_HAS_FLAG) {
		if (cg.snap->ps.powerups[PW_REDFLAG] || cg.snap->ps.powerups[PW_BLUEFLAG] || cg.snap->ps.powerups[PW_NEUTRALFLAG]) {
			return qtrue;
		}
	}
	return qfalse;
}