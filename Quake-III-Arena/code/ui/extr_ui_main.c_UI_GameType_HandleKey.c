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
typedef  scalar_t__ qboolean ;
struct TYPE_10__ {int numGameTypes; TYPE_2__* gameTypes; TYPE_1__* mapList; } ;
struct TYPE_9__ {size_t integer; } ;
struct TYPE_8__ {int integer; } ;
struct TYPE_7__ {scalar_t__ gtEnum; } ;
struct TYPE_6__ {int /*<<< orphan*/  mapLoadName; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDER_MAPS ; 
 scalar_t__ GT_TOURNAMENT ; 
 int K_ENTER ; 
 int K_KP_ENTER ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int /*<<< orphan*/  Menu_SetFeederSelection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_LoadBestScores (int /*<<< orphan*/ ,scalar_t__) ; 
 int UI_MapCountByGameType (scalar_t__) ; 
 int /*<<< orphan*/  UI_SetCapFragLimits (scalar_t__) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 TYPE_5__ uiInfo ; 
 TYPE_4__ ui_currentMap ; 
 TYPE_3__ ui_gameType ; 
 char* va (char*,size_t) ; 

__attribute__((used)) static qboolean UI_GameType_HandleKey(int flags, float *special, int key, qboolean resetMap) {
  if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER) {
		int oldCount = UI_MapCountByGameType(qtrue);

		// hard coded mess here
		if (key == K_MOUSE2) {
			ui_gameType.integer--;
			if (ui_gameType.integer == 2) {
				ui_gameType.integer = 1;
			} else if (ui_gameType.integer < 2) {
				ui_gameType.integer = uiInfo.numGameTypes - 1;
			}
		} else {
			ui_gameType.integer++;
			if (ui_gameType.integer >= uiInfo.numGameTypes) {
				ui_gameType.integer = 1;
			} else if (ui_gameType.integer == 2) {
				ui_gameType.integer = 3;
			}
		}
    
		if (uiInfo.gameTypes[ui_gameType.integer].gtEnum == GT_TOURNAMENT) {
			trap_Cvar_Set("ui_Q3Model", "1");
		} else {
			trap_Cvar_Set("ui_Q3Model", "0");
		}

		trap_Cvar_Set("ui_gameType", va("%d", ui_gameType.integer));
		UI_SetCapFragLimits(qtrue);
		UI_LoadBestScores(uiInfo.mapList[ui_currentMap.integer].mapLoadName, uiInfo.gameTypes[ui_gameType.integer].gtEnum);
		if (resetMap && oldCount != UI_MapCountByGameType(qtrue)) {
	  	trap_Cvar_Set( "ui_currentMap", "0");
			Menu_SetFeederSelection(NULL, FEEDER_MAPS, 0, NULL);
		}
    return qtrue;
  }
  return qfalse;
}