#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ rectDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  description; } ;
struct TYPE_6__ {size_t integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Text_Paint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t numServerFilters ; 
 TYPE_3__* serverFilters ; 
 TYPE_2__ ui_serverFilterType ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void UI_DrawNetFilter(rectDef_t *rect, float scale, vec4_t color, int textStyle) {
	if (ui_serverFilterType.integer < 0 || ui_serverFilterType.integer > numServerFilters) {
		ui_serverFilterType.integer = 0;
	}
  Text_Paint(rect->x, rect->y, scale, color, va("Filter: %s", serverFilters[ui_serverFilterType.integer].description), 0, 0, textStyle);
}