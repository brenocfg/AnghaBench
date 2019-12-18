#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int integer; } ;
struct TYPE_4__ {int redStatus; int blueStatus; int flagStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_ATBASE ; 
#define  GT_1FCTF 129 
#define  GT_CTF 128 
 int /*<<< orphan*/  TEAM_BLUE ; 
 int /*<<< orphan*/  TEAM_FREE ; 
 int /*<<< orphan*/  TEAM_RED ; 
 int /*<<< orphan*/  Team_SetFlagStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ g_gametype ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ teamgame ; 

void Team_InitGame( void ) {
	memset(&teamgame, 0, sizeof teamgame);

	switch( g_gametype.integer ) {
	case GT_CTF:
		teamgame.redStatus = teamgame.blueStatus = -1; // Invalid to force update
		Team_SetFlagStatus( TEAM_RED, FLAG_ATBASE );
		Team_SetFlagStatus( TEAM_BLUE, FLAG_ATBASE );
		break;
#ifdef MISSIONPACK
	case GT_1FCTF:
		teamgame.flagStatus = -1; // Invalid to force update
		Team_SetFlagStatus( TEAM_FREE, FLAG_ATBASE );
		break;
#endif
	default:
		break;
	}
}