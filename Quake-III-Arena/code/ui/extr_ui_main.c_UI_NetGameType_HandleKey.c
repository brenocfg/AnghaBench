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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {size_t numGameTypes; TYPE_1__* gameTypes; } ;
struct TYPE_5__ {size_t integer; } ;
struct TYPE_4__ {size_t gtEnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEEDER_ALLMAPS ; 
 int K_ENTER ; 
 int K_KP_ENTER ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int /*<<< orphan*/  Menu_SetFeederSelection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_MapCountByGameType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 TYPE_3__ uiInfo ; 
 TYPE_2__ ui_netGameType ; 
 char* va (char*,size_t) ; 

__attribute__((used)) static qboolean UI_NetGameType_HandleKey(int flags, float *special, int key) {
  if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER) {

		if (key == K_MOUSE2) {
			ui_netGameType.integer--;
		} else {
			ui_netGameType.integer++;
		}

    if (ui_netGameType.integer < 0) {
      ui_netGameType.integer = uiInfo.numGameTypes - 1;
		} else if (ui_netGameType.integer >= uiInfo.numGameTypes) {
      ui_netGameType.integer = 0;
    } 

  	trap_Cvar_Set( "ui_netGameType", va("%d", ui_netGameType.integer));
  	trap_Cvar_Set( "ui_actualnetGameType", va("%d", uiInfo.gameTypes[ui_netGameType.integer].gtEnum));
  	trap_Cvar_Set( "ui_currentNetMap", "0");
		UI_MapCountByGameType(qfalse);
		Menu_SetFeederSelection(NULL, FEEDER_ALLMAPS, 0, NULL);
    return qtrue;
  }
  return qfalse;
}