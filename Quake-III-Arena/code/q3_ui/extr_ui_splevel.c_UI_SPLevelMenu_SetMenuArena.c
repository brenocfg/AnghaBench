#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  map ;
struct TYPE_6__ {char** levelNames; int* levelScores; TYPE_2__* item_maps; int /*<<< orphan*/ * levelPicNames; int /*<<< orphan*/ * levelScoresSkill; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ generic; scalar_t__ shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  ART_MAP_UNKNOWN ; 
 char* Info_ValueForKey (char const*,char*) ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  QMF_GRAYED ; 
 int /*<<< orphan*/  QMF_INACTIVE ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  Q_strupr (char*) ; 
 int /*<<< orphan*/  UI_GetBestScore (int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ currentSet ; 
 TYPE_3__ levelMenuInfo ; 
 scalar_t__ selectedArenaSet ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char*) ; 

__attribute__((used)) static void UI_SPLevelMenu_SetMenuArena( int n, int level, const char *arenaInfo ) {
	char		map[MAX_QPATH];

	Q_strncpyz( map, Info_ValueForKey( arenaInfo, "map" ), sizeof(map) );

	Q_strncpyz( levelMenuInfo.levelNames[n], map, sizeof(levelMenuInfo.levelNames[n]) );
	Q_strupr( levelMenuInfo.levelNames[n] );

	UI_GetBestScore( level, &levelMenuInfo.levelScores[n], &levelMenuInfo.levelScoresSkill[n] );
	if( levelMenuInfo.levelScores[n] > 8 ) {
		levelMenuInfo.levelScores[n] = 8;
	}

	strcpy( levelMenuInfo.levelPicNames[n], va( "levelshots/%s.tga", map ) );
	if( !trap_R_RegisterShaderNoMip( levelMenuInfo.levelPicNames[n] ) ) {
		strcpy( levelMenuInfo.levelPicNames[n], ART_MAP_UNKNOWN );
	}
	levelMenuInfo.item_maps[n].shader = 0;
	if ( selectedArenaSet > currentSet ) {
		levelMenuInfo.item_maps[n].generic.flags |= QMF_GRAYED;
	}
	else {
		levelMenuInfo.item_maps[n].generic.flags &= ~QMF_GRAYED;
	}

	levelMenuInfo.item_maps[n].generic.flags &= ~QMF_INACTIVE;
}