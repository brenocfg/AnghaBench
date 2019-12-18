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
typedef  int postGameInfo_t ;
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  demoAvailable; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char const*,int,...) ; 
 int /*<<< orphan*/  FS_READ ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  UI_SetBestScores (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_FS_FCloseFile (int /*<<< orphan*/ ) ; 
 scalar_t__ trap_FS_FOpenFile (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_FS_Read (int*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ uiInfo ; 

void UI_LoadBestScores(const char *map, int game) {
	char		fileName[MAX_QPATH];
	fileHandle_t f;
	postGameInfo_t newInfo;
	memset(&newInfo, 0, sizeof(postGameInfo_t));
	Com_sprintf(fileName, MAX_QPATH, "games/%s_%i.game", map, game);
	if (trap_FS_FOpenFile(fileName, &f, FS_READ) >= 0) {
		int size = 0;
		trap_FS_Read(&size, sizeof(int), f);
		if (size == sizeof(postGameInfo_t)) {
			trap_FS_Read(&newInfo, sizeof(postGameInfo_t), f);
		}
		trap_FS_FCloseFile(f);
	}
	UI_SetBestScores(&newInfo, qfalse);

	Com_sprintf(fileName, MAX_QPATH, "demos/%s_%d.dm_%d", map, game, (int)trap_Cvar_VariableValue("protocol"));
	uiInfo.demoAvailable = qfalse;
	if (trap_FS_FOpenFile(fileName, &f, FS_READ) >= 0) {
		uiInfo.demoAvailable = qtrue;
		trap_FS_FCloseFile(f);
	} 
}