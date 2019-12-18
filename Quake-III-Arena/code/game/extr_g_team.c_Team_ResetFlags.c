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
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 int /*<<< orphan*/  TEAM_BLUE ; 
 int /*<<< orphan*/  TEAM_FREE ; 
 int /*<<< orphan*/  TEAM_RED ; 
 int /*<<< orphan*/  Team_ResetFlag (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_gametype ; 

void Team_ResetFlags( void ) {
	if( g_gametype.integer == GT_CTF ) {
		Team_ResetFlag( TEAM_RED );
		Team_ResetFlag( TEAM_BLUE );
	}
#ifdef MISSIONPACK
	else if( g_gametype.integer == GT_1FCTF ) {
		Team_ResetFlag( TEAM_FREE );
	}
#endif
}