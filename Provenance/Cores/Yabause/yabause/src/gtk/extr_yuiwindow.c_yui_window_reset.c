#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; int /*<<< orphan*/  (* reset_func ) () ;} ;
typedef  TYPE_1__ YuiWindow ;

/* Variables and functions */
 int YUI_IS_INIT ; 
 int /*<<< orphan*/  stub1 () ; 

void yui_window_reset(YuiWindow * yui) {
	if (yui->state & YUI_IS_INIT) {
		yui->reset_func();
	}
}