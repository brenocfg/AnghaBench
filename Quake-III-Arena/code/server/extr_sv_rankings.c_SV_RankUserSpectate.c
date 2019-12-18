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
struct TYPE_4__ {int /*<<< orphan*/  grank_status; } ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  QGR_STATUS_SPECTATOR ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* s_ranked_players ; 
 int /*<<< orphan*/  s_rankings_active ; 
 TYPE_1__* sv_maxclients ; 

void SV_RankUserSpectate( int index )
{
	if( !s_rankings_active )
	{
		return;
	}

	assert( s_ranked_players != NULL );
	assert( index >= 0 );
	assert( index < sv_maxclients->value );

	// GRANK_FIXME - check current status?
	s_ranked_players[index].grank_status = QGR_STATUS_SPECTATOR;
}