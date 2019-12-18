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
struct TYPE_5__ {scalar_t__ integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotInterbreedBots () ; 
 int /*<<< orphan*/  BotWriteInterbreeded (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bot_interbreed ; 
 TYPE_3__ bot_interbreedcycle ; 
 scalar_t__ bot_interbreedmatchcount ; 
 TYPE_1__ bot_interbreedwrite ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Update (TYPE_1__*) ; 

void BotInterbreedEndMatch(void) {

	if (!bot_interbreed) return;
	bot_interbreedmatchcount++;
	if (bot_interbreedmatchcount >= bot_interbreedcycle.integer) {
		bot_interbreedmatchcount = 0;
		//
		trap_Cvar_Update(&bot_interbreedwrite);
		if (strlen(bot_interbreedwrite.string)) {
			BotWriteInterbreeded(bot_interbreedwrite.string);
			trap_Cvar_Set("bot_interbreedwrite", "");
		}
		BotInterbreedBots();
	}
}