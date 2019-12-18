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
typedef  int /*<<< orphan*/  teammatename ;
typedef  int /*<<< orphan*/  bot_state_t ;
struct TYPE_2__ {int preference; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientName (int,char*,int) ; 
 int MAX_NETNAME ; 
 TYPE_1__* ctftaskpreferences ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void BotSetTeamMateTaskPreference(bot_state_t *bs, int teammate, int preference) {
	char teammatename[MAX_NETNAME];

	ctftaskpreferences[teammate].preference = preference;
	ClientName(teammate, teammatename, sizeof(teammatename));
	strcpy(ctftaskpreferences[teammate].name, teammatename);
}