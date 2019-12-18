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
struct TYPE_4__ {TYPE_1__* clientinfo; } ;
struct TYPE_3__ {void* powerups; void* curWeapon; void* armor; void* health; void* location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Argv (int) ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 TYPE_2__ cgs ; 
 int numSortedTeamPlayers ; 
 int* sortedTeamPlayers ; 

__attribute__((used)) static void CG_ParseTeamInfo( void ) {
	int		i;
	int		client;

	numSortedTeamPlayers = atoi( CG_Argv( 1 ) );

	for ( i = 0 ; i < numSortedTeamPlayers ; i++ ) {
		client = atoi( CG_Argv( i * 6 + 2 ) );

		sortedTeamPlayers[i] = client;

		cgs.clientinfo[ client ].location = atoi( CG_Argv( i * 6 + 3 ) );
		cgs.clientinfo[ client ].health = atoi( CG_Argv( i * 6 + 4 ) );
		cgs.clientinfo[ client ].armor = atoi( CG_Argv( i * 6 + 5 ) );
		cgs.clientinfo[ client ].curWeapon = atoi( CG_Argv( i * 6 + 6 ) );
		cgs.clientinfo[ client ].powerups = atoi( CG_Argv( i * 6 + 7 ) );
	}
}