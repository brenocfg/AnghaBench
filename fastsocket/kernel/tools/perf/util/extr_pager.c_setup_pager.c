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
struct TYPE_3__ {char const** argv; int in; int /*<<< orphan*/  preexec_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 char* getenv (char*) ; 
 scalar_t__ isatty (int) ; 
 char const** pager_argv ; 
 int /*<<< orphan*/  pager_preexec ; 
 TYPE_1__ pager_process ; 
 char* pager_program ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_default_config ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 int spawned_pager ; 
 scalar_t__ start_command (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  wait_for_pager ; 
 int /*<<< orphan*/  wait_for_pager_signal ; 

void setup_pager(void)
{
	const char *pager = getenv("PERF_PAGER");

	if (!isatty(1))
		return;
	if (!pager) {
		if (!pager_program)
			perf_config(perf_default_config, NULL);
		pager = pager_program;
	}
	if (!pager)
		pager = getenv("PAGER");
	if (!pager) {
		if (!access("/usr/bin/pager", X_OK))
			pager = "/usr/bin/pager";
	}
	if (!pager)
		pager = "less";
	else if (!*pager || !strcmp(pager, "cat"))
		return;

	spawned_pager = 1; /* means we are emitting to terminal */

	/* spawn the pager */
	pager_argv[2] = pager;
	pager_process.argv = pager_argv;
	pager_process.in = -1;
	pager_process.preexec_cb = pager_preexec;

	if (start_command(&pager_process))
		return;

	/* original process continues, but writes to the pipe */
	dup2(pager_process.in, 1);
	if (isatty(2))
		dup2(pager_process.in, 2);
	close(pager_process.in);

	/* this makes sure that the parent terminates after the pager */
	sigchain_push_common(wait_for_pager_signal);
	atexit(wait_for_pager);
}