#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ rectDef_t ;
struct TYPE_7__ {scalar_t__ currentServerCinematic; } ;
struct TYPE_10__ {scalar_t__ mapCount; TYPE_1__ serverStatus; } ;
struct TYPE_9__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_DrawNetMapPreview (TYPE_2__*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_CIN_DrawCinematic (scalar_t__) ; 
 int /*<<< orphan*/  trap_CIN_RunCinematic (scalar_t__) ; 
 int /*<<< orphan*/  trap_CIN_SetExtents (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 TYPE_4__ uiInfo ; 
 TYPE_3__ ui_currentNetMap ; 

__attribute__((used)) static void UI_DrawNetMapCinematic(rectDef_t *rect, float scale, vec4_t color) {
	if (ui_currentNetMap.integer < 0 || ui_currentNetMap.integer > uiInfo.mapCount) {
		ui_currentNetMap.integer = 0;
		trap_Cvar_Set("ui_currentNetMap", "0");
	}

	if (uiInfo.serverStatus.currentServerCinematic >= 0) {
	  trap_CIN_RunCinematic(uiInfo.serverStatus.currentServerCinematic);
	  trap_CIN_SetExtents(uiInfo.serverStatus.currentServerCinematic, rect->x, rect->y, rect->w, rect->h);
 	  trap_CIN_DrawCinematic(uiInfo.serverStatus.currentServerCinematic);
	} else {
		UI_DrawNetMapPreview(rect, scale, color);
	}
}