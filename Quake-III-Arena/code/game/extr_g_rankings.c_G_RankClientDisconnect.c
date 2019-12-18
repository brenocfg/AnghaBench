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
struct TYPE_6__ {int* persistant; } ;
struct TYPE_7__ {int enterTime; } ;
struct TYPE_8__ {TYPE_1__ ps; TYPE_2__ pers; } ;
typedef  TYPE_3__ gclient_t ;
struct TYPE_10__ {TYPE_3__* client; } ;
struct TYPE_9__ {scalar_t__ warmupTime; int time; } ;

/* Variables and functions */
 size_t PERS_MATCH_RATING ; 
 int /*<<< orphan*/  QGR_KEY_MATCH_RATING ; 
 TYPE_5__* g_entities ; 
 TYPE_4__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void G_RankClientDisconnect( int self )
{
	gclient_t*	client;
	int			time;
	int			match_rating;
	
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	// match rating
	client = g_entities[self].client;
	time = (level.time - client->pers.enterTime) / 1000;
	if( time < 60 )
	{
		match_rating = 0;
	}
	else
	{
		match_rating = client->ps.persistant[PERS_MATCH_RATING] / time;
	}
	trap_RankReportInt( self, -1, QGR_KEY_MATCH_RATING, match_rating, 0 );
}