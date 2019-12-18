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
struct TYPE_2__ {int effectsColor; } ;

/* Variables and functions */
 int K_ENTER ; 
 int K_KP_ENTER ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ uiInfo ; 
 int /*<<< orphan*/ * uitogamecode ; 

__attribute__((used)) static qboolean UI_Effects_HandleKey(int flags, float *special, int key) {
  if (key == K_MOUSE1 || key == K_MOUSE2 || key == K_ENTER || key == K_KP_ENTER) {

		if (key == K_MOUSE2) {
	    uiInfo.effectsColor--;
		} else {
	    uiInfo.effectsColor++;
		}

    if( uiInfo.effectsColor > 6 ) {
	  	uiInfo.effectsColor = 0;
		} else if (uiInfo.effectsColor < 0) {
	  	uiInfo.effectsColor = 6;
		}

	  trap_Cvar_SetValue( "color1", uitogamecode[uiInfo.effectsColor] );
    return qtrue;
  }
  return qfalse;
}