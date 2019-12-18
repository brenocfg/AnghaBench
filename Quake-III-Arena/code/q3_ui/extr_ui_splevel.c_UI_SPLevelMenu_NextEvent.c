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
struct TYPE_2__ {int /*<<< orphan*/  selectedArenaInfo; } ;

/* Variables and functions */
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_SPSkillMenu (int /*<<< orphan*/ ) ; 
 scalar_t__ currentSet ; 
 TYPE_1__ levelMenuInfo ; 
 int selectedArena ; 
 scalar_t__ selectedArenaSet ; 

__attribute__((used)) static void UI_SPLevelMenu_NextEvent( void* ptr, int notification ) {
	if (notification != QM_ACTIVATED) {
		return;
	}

	if ( selectedArenaSet > currentSet ) {
		return;
	}

	if ( selectedArena == -1 ) {
		selectedArena = 0;
	}

	UI_SPSkillMenu( levelMenuInfo.selectedArenaInfo );
}