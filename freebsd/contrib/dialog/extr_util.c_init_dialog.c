#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ use_shadow; scalar_t__ use_colors; int /*<<< orphan*/  screen_initialized; int /*<<< orphan*/  no_mouse; int /*<<< orphan*/ * screen_output; int /*<<< orphan*/ * pipe_input; int /*<<< orphan*/  aspect_ratio; int /*<<< orphan*/  tab_len; int /*<<< orphan*/ * output; } ;
struct TYPE_3__ {int /*<<< orphan*/  keep_tite; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ASPECT_RATIO ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  TAB_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USE_COLORS ; 
 scalar_t__ USE_SHADOW ; 
 int /*<<< orphan*/  cbreak () ; 
 scalar_t__ clear_screen ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_2__ dialog_state ; 
 scalar_t__ dialog_tty () ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_clear () ; 
 int /*<<< orphan*/  dlg_color_setup () ; 
 int /*<<< orphan*/  dlg_exiterr (char*) ; 
 int dlg_parse_rc () ; 
 int dup (scalar_t__) ; 
 int /*<<< orphan*/  dup2 (scalar_t__,scalar_t__) ; 
 scalar_t__ enter_ca_mode ; 
 scalar_t__ exit_ca_mode ; 
 void* fdopen (int,char*) ; 
 scalar_t__ fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flushinp () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ freopen (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initscr () ; 
 scalar_t__ isatty (scalar_t__) ; 
 scalar_t__ isprivate (scalar_t__) ; 
 scalar_t__ key_mouse ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_open () ; 
 int /*<<< orphan*/  my_putc ; 
 scalar_t__ newterm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noecho () ; 
 int open_terminal (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  tputs (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
init_dialog(FILE *input, FILE *output)
{
    int fd1, fd2;
    char *device = 0;

    setlocale(LC_ALL, "");

    dialog_state.output = output;
    dialog_state.tab_len = TAB_LEN;
    dialog_state.aspect_ratio = DEFAULT_ASPECT_RATIO;
#ifdef HAVE_COLOR
    dialog_state.use_colors = USE_COLORS;	/* use colors by default? */
    dialog_state.use_shadow = USE_SHADOW;	/* shadow dialog boxes by default? */
#endif

#ifdef HAVE_RC_FILE
    if (dlg_parse_rc() == -1)	/* Read the configuration file */
	dlg_exiterr("init_dialog: dlg_parse_rc");
#endif

    /*
     * Some widgets (such as gauge) may read from the standard input.  Pipes
     * only connect stdout/stdin, so there is not much choice.  But reading a
     * pipe would get in the way of curses' normal reading stdin for getch.
     *
     * As in the --stdout (see below), reopening the terminal does not always
     * work properly.  dialog provides a --pipe-fd option for this purpose.  We
     * test that case first (differing fileno's for input/stdin).  If the
     * fileno's are equal, but we're not reading from a tty, see if we can open
     * /dev/tty.
     */
    dialog_state.pipe_input = stdin;
    if (fileno(input) != fileno(stdin)) {
	if ((fd1 = dup(fileno(input))) >= 0
	    && (fd2 = dup(fileno(stdin))) >= 0) {
	    (void) dup2(fileno(input), fileno(stdin));
	    dialog_state.pipe_input = fdopen(fd2, "r");
	    if (fileno(stdin) != 0)	/* some functions may read fd #0 */
		(void) dup2(fileno(stdin), 0);
	} else {
	    dlg_exiterr("cannot open tty-input");
	}
	close(fd1);
    } else if (!isatty(fileno(stdin))) {
	if ((fd1 = open_terminal(&device, O_RDONLY)) >= 0) {
	    if ((fd2 = dup(fileno(stdin))) >= 0) {
		dialog_state.pipe_input = fdopen(fd2, "r");
		if (freopen(device, "r", stdin) == 0)
		    dlg_exiterr("cannot open tty-input");
		if (fileno(stdin) != 0)		/* some functions may read fd #0 */
		    (void) dup2(fileno(stdin), 0);
	    }
	    close(fd1);
	}
	free(device);
    }

    /*
     * If stdout is not a tty and dialog is called with the --stdout option, we
     * have to provide for a way to write to the screen.
     *
     * The curses library normally writes its output to stdout, leaving stderr
     * free for scripting.  Scripts are simpler when stdout is redirected.  The
     * newterm function is useful; it allows us to specify where the output
     * goes.  Reopening the terminal is not portable since several
     * configurations do not allow this to work properly:
     *
     * a) some getty implementations (and possibly broken tty drivers, e.g., on
     *    HPUX 10 and 11) cause stdin to act as if it is still in cooked mode
     *    even though results from ioctl's state that it is successfully
     *    altered to raw mode.  Broken is the proper term.
     *
     * b) the user may not have permissions on the device, e.g., if one su's
     *    from the login user to another non-privileged user.
     */
    if (!isatty(fileno(stdout))
	&& (fileno(stdout) == fileno(output) || dialog_tty())) {
	if ((fd1 = open_terminal(&device, O_WRONLY)) >= 0
	    && (dialog_state.screen_output = fdopen(fd1, "w")) != 0) {
	    if (newterm(NULL, dialog_state.screen_output, stdin) == 0) {
		dlg_exiterr("cannot initialize curses");
	    }
	    free(device);
	} else {
	    dlg_exiterr("cannot open tty-output");
	}
    } else {
	dialog_state.screen_output = stdout;
	(void) initscr();
    }
#ifdef NCURSES_VERSION
    /*
     * Cancel xterm's alternate-screen mode.
     */
    if (!dialog_vars.keep_tite
	&& (fileno(dialog_state.screen_output) != fileno(stdout)
	    || isatty(fileno(dialog_state.screen_output)))
	&& key_mouse != 0	/* xterm and kindred */
	&& isprivate(enter_ca_mode)
	&& isprivate(exit_ca_mode)) {
	/*
	 * initscr() or newterm() already wrote enter_ca_mode as a side
	 * effect of initializing the screen.  It would be nice to not even
	 * do that, but we do not really have access to the correct copy of
	 * the terminfo description until those functions have been invoked.
	 */
	(void) refresh();
	(void) tputs(exit_ca_mode, 0, my_putc);
	(void) tputs(clear_screen, 0, my_putc);
	/*
	 * Prevent ncurses from switching "back" to the normal screen when
	 * exiting from dialog.  That would move the cursor to the original
	 * location saved in xterm.  Normally curses sets the cursor position
	 * to the first line after the display, but the alternate screen
	 * switching is done after that point.
	 *
	 * Cancelling the strings altogether also works around the buggy
	 * implementation of alternate-screen in rxvt, etc., which clear
	 * more of the display than they should.
	 */
	enter_ca_mode = 0;
	exit_ca_mode = 0;
    }
#endif
#ifdef HAVE_FLUSHINP
    (void) flushinp();
#endif
    (void) keypad(stdscr, TRUE);
    (void) cbreak();
    (void) noecho();

    if (!dialog_state.no_mouse) {
	mouse_open();
    }

    dialog_state.screen_initialized = TRUE;

#ifdef HAVE_COLOR
    if (dialog_state.use_colors || dialog_state.use_shadow)
	dlg_color_setup();	/* Set up colors */
#endif

    /* Set screen to screen attribute */
    dlg_clear();
}