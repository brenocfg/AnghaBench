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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int botIndex; int characterCount; } ;

/* Variables and functions */
 int GT_TEAM ; 
 int K_ENTER ; 
 int K_KP_ENTER ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int UI_GetNumBots () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int trap_Cvar_VariableValue (char*) ; 
 TYPE_1__ uiInfo ; 

__attribute__((used)) static qboolean UI_BotName_HandleKey(int flags, float *special, int key) {
  if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER) {
		int game = trap_Cvar_VariableValue("g_gametype");
		int value = uiInfo.botIndex;

		if (key == K_MOUSE2) {
			value--;
		} else {
			value++;
		}

		if (game >= GT_TEAM) {
			if (value >= uiInfo.characterCount + 2) {
				value = 0;
			} else if (value < 0) {
				value = uiInfo.characterCount + 2 - 1;
			}
		} else {
			if (value >= UI_GetNumBots() + 2) {
				value = 0;
			} else if (value < 0) {
				value = UI_GetNumBots() + 2 - 1;
			}
		}
		uiInfo.botIndex = value;
    return qtrue;
  }
  return qfalse;
}