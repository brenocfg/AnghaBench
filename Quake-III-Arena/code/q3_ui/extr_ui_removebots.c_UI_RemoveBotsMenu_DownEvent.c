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
struct TYPE_2__ {scalar_t__ baseBotNum; scalar_t__ numBots; } ;

/* Variables and functions */
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_RemoveBotsMenu_SetBotNames () ; 
 TYPE_1__ removeBotsMenuInfo ; 

__attribute__((used)) static void UI_RemoveBotsMenu_DownEvent( void* ptr, int event ) {
	if (event != QM_ACTIVATED) {
		return;
	}

	if( removeBotsMenuInfo.baseBotNum + 7 < removeBotsMenuInfo.numBots ) {
		removeBotsMenuInfo.baseBotNum++;
		UI_RemoveBotsMenu_SetBotNames();
	}
}