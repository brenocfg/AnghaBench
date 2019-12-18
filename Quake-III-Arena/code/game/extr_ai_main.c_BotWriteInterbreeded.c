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
struct TYPE_2__ {int num_kills; int num_deaths; int /*<<< orphan*/  gs; scalar_t__ inuse; } ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 TYPE_1__** botstates ; 
 int /*<<< orphan*/  trap_BotSaveGoalFuzzyLogic (int /*<<< orphan*/ ,char*) ; 

void BotWriteInterbreeded(char *filename) {
	float rank, bestrank;
	int i, bestbot;

	bestrank = 0;
	bestbot = -1;
	// get the best bot
	for (i = 0; i < MAX_CLIENTS; i++) {
		if ( botstates[i] && botstates[i]->inuse ) {
			rank = botstates[i]->num_kills * 2 - botstates[i]->num_deaths;
		}
		else {
			rank = -1;
		}
		if (rank > bestrank) {
			bestrank = rank;
			bestbot = i;
		}
	}
	if (bestbot >= 0) {
		//write out the new goal fuzzy logic
		trap_BotSaveGoalFuzzyLogic(botstates[bestbot]->gs, filename);
	}
}