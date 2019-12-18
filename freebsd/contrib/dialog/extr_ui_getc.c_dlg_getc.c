#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_12__ {TYPE_1__* getc_redirect; int /*<<< orphan*/  getc_callbacks; int /*<<< orphan*/  screen_output; } ;
struct TYPE_11__ {int timeout_secs; int /*<<< orphan*/  help_file; } ;
struct TYPE_10__ {int /*<<< orphan*/  keep_win; int /*<<< orphan*/ * win; int /*<<< orphan*/  (* handle_getc ) (TYPE_1__*,int,int,int*) ;} ;
typedef  TYPE_1__ DIALOG_CALLBACK ;

/* Variables and functions */
#define  CHR_LITERAL 136 
#define  CHR_REPAINT 135 
#define  CHR_TRACE 134 
#define  DLGK_FIELD_NEXT 133 
#define  DLGK_FIELD_PREV 132 
#define  DLGK_HELPFILE 131 
 int const DLG_CTRL (char) ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
#define  ERR 130 
 int ESC ; 
 int FALSE ; 
#define  KEY_BTAB 129 
#define  TAB 128 
 int TRUE ; 
 int WTIMEOUT_VAL ; 
 int /*<<< orphan*/  check_inputs () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  curscr ; 
 int /*<<< orphan*/  dialog_helpfile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ dialog_state ; 
 TYPE_8__ dialog_vars ; 
 int dlg_lookup_key (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dlg_raise_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_remove_callback (TYPE_1__*) ; 
 int /*<<< orphan*/  dlg_trace_chr (int,int) ; 
 int /*<<< orphan*/  dlg_trace_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  handle_inputs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isBeforeChr (int const) ; 
 int /*<<< orphan*/  isBeforeFkey (int const) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int) ; 
 scalar_t__ may_handle_inputs () ; 
 TYPE_1__* next_callback (TYPE_1__*) ; 
 TYPE_1__* prev_callback (TYPE_1__*) ; 
 int really_getch (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int*) ; 
 scalar_t__ time (scalar_t__*) ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valid_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wtimeout (int /*<<< orphan*/ *,int) ; 

int
dlg_getc(WINDOW *win, int *fkey)
{
    WINDOW *save_win = win;
    int ch = ERR;
    int before_chr;
    int before_fkey;
    int result;
    bool done = FALSE;
    bool literal = FALSE;
    DIALOG_CALLBACK *p = 0;
    int interval = (dialog_vars.timeout_secs * 1000);
    time_t expired = time((time_t *) 0) + dialog_vars.timeout_secs;
    time_t current;

    if (may_handle_inputs())
	wtimeout(win, WTIMEOUT_VAL);
    else if (interval > 0)
	wtimeout(win, interval);

    while (!done) {
	bool handle_others = FALSE;

	/*
	 * If there was no pending file-input, check the keyboard.
	 */
	ch = really_getch(win, fkey);
	if (literal) {
	    done = TRUE;
	    continue;
	}

	before_chr = ch;
	before_fkey = *fkey;

	ch = dlg_lookup_key(win, ch, fkey);
	dlg_trace_chr(ch, *fkey);

	current = time((time_t *) 0);

	/*
	 * If we acquired a fkey value, then it is one of dialog's builtin
	 * codes such as DLGK_HELPFILE.
	 */
	if (!*fkey || *fkey != before_fkey) {
	    switch (ch) {
	    case CHR_LITERAL:
		literal = TRUE;
		keypad(win, FALSE);
		continue;
	    case CHR_REPAINT:
		(void) touchwin(win);
		(void) wrefresh(curscr);
		break;
	    case ERR:		/* wtimeout() in effect; check for file I/O */
		if (interval > 0
		    && current >= expired) {
		    DLG_TRACE(("# dlg_getc: timeout expired\n"));
		    ch = ESC;
		    done = TRUE;
		} else if (!valid_file(stdin)
			   || !valid_file(dialog_state.screen_output)) {
		    DLG_TRACE(("# dlg_getc: input or output is invalid\n"));
		    ch = ESC;
		    done = TRUE;
		} else if (check_inputs()) {
		    if (handle_inputs(win))
			dlg_raise_window(win);
		    else
			done = TRUE;
		} else {
		    done = (interval <= 0);
		}
		break;
	    case DLGK_HELPFILE:
		if (dialog_vars.help_file) {
		    int yold, xold;
		    getyx(win, yold, xold);
		    dialog_helpfile("HELP", dialog_vars.help_file, 0, 0);
		    dlg_raise_window(win);
		    wmove(win, yold, xold);
		}
		continue;
	    case DLGK_FIELD_PREV:
		/* FALLTHRU */
	    case KEY_BTAB:
		/* FALLTHRU */
	    case DLGK_FIELD_NEXT:
		/* FALLTHRU */
	    case TAB:
		/* Handle tab/backtab as a special case for traversing between
		 * the nominal "current" window, and other windows having
		 * callbacks.  If the nominal (control) window closes, we'll
		 * close the windows with callbacks.
		 */
		if (dialog_state.getc_callbacks != 0 &&
		    (isBeforeChr(TAB) ||
		     isBeforeFkey(KEY_BTAB))) {
		    p = (isBeforeChr(TAB)
			 ? next_callback(p)
			 : prev_callback(p));
		    if ((dialog_state.getc_redirect = p) != 0) {
			win = p->win;
		    } else {
			win = save_win;
		    }
		    dlg_raise_window(win);
		    break;
		}
		/* FALLTHRU */
	    default:
#ifdef NO_LEAKS
		if (isBeforeChr(DLG_CTRL('P'))) {
		    /* for testing, ^P closes the connection */
		    close(0);
		    close(1);
		    close(2);
		    break;
		}
#endif
		handle_others = TRUE;
		break;
#ifdef HAVE_DLG_TRACE
	    case CHR_TRACE:
		dlg_trace_win(win);
		break;
#endif
	    }
	} else {
	    handle_others = TRUE;
	}

	if (handle_others) {
	    if ((p = dialog_state.getc_redirect) != 0) {
		if (!(p->handle_getc(p, ch, *fkey, &result))) {
		    done = (p->win == save_win) && (!p->keep_win);
		    dlg_remove_callback(p);
		    dialog_state.getc_redirect = 0;
		    win = save_win;
		}
	    } else {
		done = TRUE;
	    }
	}
    }
    if (literal)
	keypad(win, TRUE);
    return ch;
}