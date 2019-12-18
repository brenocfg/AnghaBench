#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_4__ {int x; int w; scalar_t__ h; scalar_t__ y; } ;
typedef  TYPE_1__ rectDef_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_5__ {scalar_t__* killerName; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_GetKillerText () ; 
 int /*<<< orphan*/  CG_Text_Paint (int,scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CG_Text_Width (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 TYPE_2__ cg ; 

__attribute__((used)) static void CG_DrawKiller(rectDef_t *rect, float scale, vec4_t color, qhandle_t shader, int textStyle ) {
	// fragged by ... line
	if ( cg.killerName[0] ) {
		int x = rect->x + rect->w / 2;
	  CG_Text_Paint(x - CG_Text_Width(CG_GetKillerText(), scale, 0) / 2, rect->y + rect->h, scale, color, CG_GetKillerText(), 0, 0, textStyle);
	}
	
}