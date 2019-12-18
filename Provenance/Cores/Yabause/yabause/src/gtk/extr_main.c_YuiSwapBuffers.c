#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  YUI_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_window_update (int /*<<< orphan*/ ) ; 

void YuiSwapBuffers(void) {
	yui_window_update(YUI_WINDOW(yui));
}