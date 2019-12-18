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
 int /*<<< orphan*/  EL_ADDFN ; 
 int /*<<< orphan*/  EL_BIND ; 
 int /*<<< orphan*/  EL_EDITOR ; 
 int /*<<< orphan*/  EL_HIST ; 
 int /*<<< orphan*/  EL_PROMPT ; 
 scalar_t__ Eflag ; 
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 scalar_t__ Vflag ; 
 int /*<<< orphan*/ * _el_fn_complete ; 
 int /*<<< orphan*/  arg0 ; 
 scalar_t__ editing ; 
 int /*<<< orphan*/ * el ; 
 int /*<<< orphan*/  el_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * el_in ; 
 int /*<<< orphan*/ * el_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * el_out ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  el_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* fdopen (int,char*) ; 
 int /*<<< orphan*/  getprompt ; 
 int /*<<< orphan*/ * hist ; 
 int /*<<< orphan*/  history ; 
 int /*<<< orphan*/  history_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * history_init () ; 
 int /*<<< orphan*/  histsizeval () ; 
 scalar_t__ iflag ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 char* lookupvar (char*) ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sethistsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

void
histedit(void)
{

#define editing (Eflag || Vflag)

	if (iflag) {
		if (!hist) {
			/*
			 * turn history on
			 */
			INTOFF;
			hist = history_init();
			INTON;

			if (hist != NULL)
				sethistsize(histsizeval());
			else
				out2fmt_flush("sh: can't initialize history\n");
		}
		if (editing && !el && isatty(0)) { /* && isatty(2) ??? */
			/*
			 * turn editing on
			 */
			char *term;

			INTOFF;
			if (el_in == NULL)
				el_in = fdopen(0, "r");
			if (el_out == NULL)
				el_out = fdopen(2, "w");
			if (el_in == NULL || el_out == NULL)
				goto bad;
			term = lookupvar("TERM");
			if (term)
				setenv("TERM", term, 1);
			else
				unsetenv("TERM");
			el = el_init(arg0, el_in, el_out, el_out);
			if (el != NULL) {
				if (hist)
					el_set(el, EL_HIST, history, hist);
				el_set(el, EL_PROMPT, getprompt);
				el_set(el, EL_ADDFN, "sh-complete",
				    "Filename completion",
				    _el_fn_complete);
			} else {
bad:
				out2fmt_flush("sh: can't initialize editing\n");
			}
			INTON;
		} else if (!editing && el) {
			INTOFF;
			el_end(el);
			el = NULL;
			INTON;
		}
		if (el) {
			if (Vflag)
				el_set(el, EL_EDITOR, "vi");
			else if (Eflag)
				el_set(el, EL_EDITOR, "emacs");
			el_set(el, EL_BIND, "^I", "sh-complete", NULL);
			el_source(el, NULL);
		}
	} else {
		INTOFF;
		if (el) {	/* no editing if not interactive */
			el_end(el);
			el = NULL;
		}
		if (hist) {
			history_end(hist);
			hist = NULL;
		}
		INTON;
	}
}