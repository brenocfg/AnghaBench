#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* string; } ;
struct TYPE_9__ {scalar_t__ curvalue; } ;
struct TYPE_16__ {scalar_t__ gametype; TYPE_7__* playerTeam; TYPE_5__* playerType; TYPE_4__* playerName; TYPE_2__ player0; TYPE_1__ dedicated; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_15__ {TYPE_6__ generic; } ;
struct TYPE_13__ {int curvalue; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_12__ {TYPE_3__ generic; } ;

/* Variables and functions */
 scalar_t__ GT_TEAM ; 
 int PLAYER_SLOTS ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
 TYPE_8__ s_serveroptions ; 

__attribute__((used)) static void ServerOptions_SetPlayerItems( void ) {
	int		start;
	int		n;

	// types
//	for( n = 0; n < PLAYER_SLOTS; n++ ) {
//		if( (!s_serveroptions.multiplayer) && (n > 0) && (s_serveroptions.playerType[n].curvalue == 0) ) {
//			s_serveroptions.playerType[n].curvalue = 1;
//		}
//	}

	// names
	if( s_serveroptions.dedicated.curvalue == 0 ) {
		s_serveroptions.player0.string = "Human";
		s_serveroptions.playerName[0].generic.flags &= ~QMF_HIDDEN;

		start = 1;
	}
	else {
		s_serveroptions.player0.string = "Open";
		start = 0;
	}
	for( n = start; n < PLAYER_SLOTS; n++ ) {
		if( s_serveroptions.playerType[n].curvalue == 1 ) {
			s_serveroptions.playerName[n].generic.flags &= ~(QMF_INACTIVE|QMF_HIDDEN);
		}
		else {
			s_serveroptions.playerName[n].generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		}
	}

	// teams
	if( s_serveroptions.gametype < GT_TEAM ) {
		return;
	}
	for( n = start; n < PLAYER_SLOTS; n++ ) {
		if( s_serveroptions.playerType[n].curvalue == 2 ) {
			s_serveroptions.playerTeam[n].generic.flags |= (QMF_INACTIVE|QMF_HIDDEN);
		}
		else {
			s_serveroptions.playerTeam[n].generic.flags &= ~(QMF_INACTIVE|QMF_HIDDEN);
		}
	}
}