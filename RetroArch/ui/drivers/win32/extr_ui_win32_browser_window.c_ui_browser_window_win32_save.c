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
typedef  int /*<<< orphan*/  ui_browser_window_state_t ;

/* Variables and functions */
 int ui_browser_window_win32_core (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool ui_browser_window_win32_save(ui_browser_window_state_t *state)
{
   return ui_browser_window_win32_core(state, true);
}