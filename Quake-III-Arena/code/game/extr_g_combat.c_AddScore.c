#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_10__ {TYPE_1__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_11__ {int* teamScores; scalar_t__ warmupTime; } ;
struct TYPE_9__ {int* persistant; } ;
struct TYPE_8__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CalculateRanks () ; 
 scalar_t__ GT_TEAM ; 
 size_t PERS_SCORE ; 
 size_t PERS_TEAM ; 
 int /*<<< orphan*/  ScorePlum (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ g_gametype ; 
 TYPE_4__ level ; 

void AddScore( gentity_t *ent, vec3_t origin, int score ) {
	if ( !ent->client ) {
		return;
	}
	// no scoring during pre-match warmup
	if ( level.warmupTime ) {
		return;
	}
	// show score plum
	ScorePlum(ent, origin, score);
	//
	ent->client->ps.persistant[PERS_SCORE] += score;
	if ( g_gametype.integer == GT_TEAM )
		level.teamScores[ ent->client->ps.persistant[PERS_TEAM] ] += score;
	CalculateRanks();
}