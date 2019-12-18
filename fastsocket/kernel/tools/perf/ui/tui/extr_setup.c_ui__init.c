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
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SL_KEY_UNTAB ; 
 int /*<<< orphan*/  SLkp_define_keysym (char*,int /*<<< orphan*/ ) ; 
 int SLkp_init () ; 
 int /*<<< orphan*/  hist_browser__init_hpp () ; 
 int /*<<< orphan*/  newtInit () ; 
 int /*<<< orphan*/  newtSetSuspendCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newt_suspend ; 
 int /*<<< orphan*/  perf_error__register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_tui_eops ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui__signal ; 
 int /*<<< orphan*/  ui_browser__init () ; 
 int /*<<< orphan*/  ui_helpline__init () ; 
 int /*<<< orphan*/  ui_progress__init () ; 

int ui__init(void)
{
	int err;

	newtInit();
	err = SLkp_init();
	if (err < 0) {
		pr_err("TUI initialization failed.\n");
		goto out;
	}

	SLkp_define_keysym((char *)"^(kB)", SL_KEY_UNTAB);

	newtSetSuspendCallback(newt_suspend, NULL);
	ui_helpline__init();
	ui_browser__init();
	ui_progress__init();

	signal(SIGSEGV, ui__signal);
	signal(SIGFPE, ui__signal);
	signal(SIGINT, ui__signal);
	signal(SIGQUIT, ui__signal);
	signal(SIGTERM, ui__signal);

	perf_error__register(&perf_tui_eops);

	hist_browser__init_hpp();
out:
	return err;
}