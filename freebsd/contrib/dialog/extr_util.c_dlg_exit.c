#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  table ;
struct TYPE_2__ {scalar_t__ input; scalar_t__ pipe_input; } ;

/* Variables and functions */
#define  DLG_EXIT_CANCEL 134 
#define  DLG_EXIT_ERROR 133 
#define  DLG_EXIT_ESC 132 
#define  DLG_EXIT_EXTRA 131 
#define  DLG_EXIT_HELP 130 
#define  DLG_EXIT_ITEM_HELP 129 
#define  DLG_EXIT_OK 128 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _dlg_inputstr_leaks () ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  _nc_free_and_exit (int) ; 
 TYPE_1__ dialog_state ; 
 int /*<<< orphan*/  dlg_trace (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 char* getenv (char const*) ; 
 scalar_t__ stdin ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

void
dlg_exit(int code)
{
    /* *INDENT-OFF* */
    static const struct {
	int code;
	const char *name;
    } table[] = {
	{ DLG_EXIT_CANCEL, 	"DIALOG_CANCEL" },
	{ DLG_EXIT_ERROR,  	"DIALOG_ERROR" },
	{ DLG_EXIT_ESC,	   	"DIALOG_ESC" },
	{ DLG_EXIT_EXTRA,  	"DIALOG_EXTRA" },
	{ DLG_EXIT_HELP,   	"DIALOG_HELP" },
	{ DLG_EXIT_OK,	   	"DIALOG_OK" },
	{ DLG_EXIT_ITEM_HELP,	"DIALOG_ITEM_HELP" },
    };
    /* *INDENT-ON* */

    unsigned n;
    char *name;
    char *temp;
    long value;
    bool overridden = FALSE;

  retry:
    for (n = 0; n < sizeof(table) / sizeof(table[0]); n++) {
	if (table[n].code == code) {
	    if ((name = getenv(table[n].name)) != 0) {
		value = strtol(name, &temp, 0);
		if (temp != 0 && temp != name && *temp == '\0') {
		    code = (int) value;
		    overridden = TRUE;
		}
	    }
	    break;
	}
    }

    /*
     * Prior to 2004/12/19, a widget using --item-help would exit with "OK"
     * if the help button were selected.  Now we want to exit with "HELP",
     * but allow the environment variable to override.
     */
    if (code == DLG_EXIT_ITEM_HELP && !overridden) {
	code = DLG_EXIT_HELP;
	goto retry;
    }
#ifdef HAVE_DLG_TRACE
    dlg_trace((const char *) 0);	/* close it */
#endif

#ifdef NO_LEAKS
    _dlg_inputstr_leaks();
#if defined(NCURSES_VERSION) && defined(HAVE__NC_FREE_AND_EXIT)
    _nc_free_and_exit(code);
#endif
#endif

    if (dialog_state.input == stdin) {
	exit(code);
    } else {
	/*
	 * Just in case of using --input-fd option, do not
	 * call atexit functions of ncurses which may hang.
	 */
	if (dialog_state.input) {
	    fclose(dialog_state.input);
	    dialog_state.input = 0;
	}
	if (dialog_state.pipe_input) {
	    if (dialog_state.pipe_input != stdin) {
		fclose(dialog_state.pipe_input);
		dialog_state.pipe_input = 0;
	    }
	}
	_exit(code);
    }
}