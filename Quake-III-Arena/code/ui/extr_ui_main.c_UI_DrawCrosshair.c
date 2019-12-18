#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec4_t ;
struct TYPE_8__ {scalar_t__ h; int /*<<< orphan*/  w; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ rectDef_t ;
struct TYPE_6__ {int /*<<< orphan*/ * crosshairShader; } ;
struct TYPE_7__ {TYPE_1__ Assets; } ;
struct TYPE_9__ {size_t currentCrosshair; TYPE_2__ uiDC; } ;

/* Variables and functions */
 size_t NUM_CROSSHAIRS ; 
 int /*<<< orphan*/  UI_DrawHandlePic (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_SetColor (int /*<<< orphan*/ *) ; 
 TYPE_4__ uiInfo ; 

__attribute__((used)) static void UI_DrawCrosshair(rectDef_t *rect, float scale, vec4_t color) {
 	trap_R_SetColor( color );
	if (uiInfo.currentCrosshair < 0 || uiInfo.currentCrosshair >= NUM_CROSSHAIRS) {
		uiInfo.currentCrosshair = 0;
	}
	UI_DrawHandlePic( rect->x, rect->y - rect->h, rect->w, rect->h, uiInfo.uiDC.Assets.crosshairShader[uiInfo.currentCrosshair]);
 	trap_R_SetColor( NULL );
}