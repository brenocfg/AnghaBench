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
 int /*<<< orphan*/  SLang_reset_tty () ; 
 int /*<<< orphan*/  SLsmg_refresh () ; 
 int /*<<< orphan*/  SLsmg_reset_smg () ; 
 int /*<<< orphan*/  SLtt_set_cursor_visibility (int) ; 
 int /*<<< orphan*/  perf_error__unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_tui_eops ; 
 int /*<<< orphan*/  ui__question_window (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_helpline__last_msg ; 

void ui__exit(bool wait_for_ok)
{
	if (wait_for_ok)
		ui__question_window("Fatal Error",
				    ui_helpline__last_msg,
				    "Press any key...", 0);

	SLtt_set_cursor_visibility(1);
	SLsmg_refresh();
	SLsmg_reset_smg();
	SLang_reset_tty();

	perf_error__unregister(&perf_tui_eops);
}