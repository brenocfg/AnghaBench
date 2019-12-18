#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_1__ vec4_t ;
struct TYPE_5__ {int /*<<< orphan*/  FPS; int /*<<< orphan*/  (* drawText ) (int,int,double,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__* DC ; 
 int Menu_Count () ; 
 int /*<<< orphan*/  Menu_Paint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Menus ; 
 int /*<<< orphan*/  captureData ; 
 int /*<<< orphan*/  captureFunc (int /*<<< orphan*/ ) ; 
 scalar_t__ debugMode ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  stub1 (int,int,double,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void Menu_PaintAll() {
	int i;
	if (captureFunc) {
		captureFunc(captureData);
	}

	for (i = 0; i < Menu_Count(); i++) {
		Menu_Paint(&Menus[i], qfalse);
	}

	if (debugMode) {
		vec4_t v = {1, 1, 1, 1};
		DC->drawText(5, 25, .5, v, va("fps: %f", DC->FPS), 0, 0, 0);
	}
}