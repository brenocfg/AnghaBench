#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  itemweightconfig; } ;
typedef  TYPE_1__ bot_goalstate_t ;

/* Variables and functions */
 TYPE_1__* BotGoalStateFromHandle (int) ; 
 int /*<<< orphan*/  EvolveWeightConfig (int /*<<< orphan*/ ) ; 

void BotMutateGoalFuzzyLogic(int goalstate, float range)
{
	bot_goalstate_t *gs;

	gs = BotGoalStateFromHandle(goalstate);

	EvolveWeightConfig(gs->itemweightconfig);
}