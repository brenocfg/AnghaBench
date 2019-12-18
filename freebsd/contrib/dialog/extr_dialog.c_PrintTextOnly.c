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
typedef  int eOptions ;
struct TYPE_2__ {int text_height; int text_width; int /*<<< orphan*/  output; int /*<<< orphan*/  text_only; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 scalar_t__ COLS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IgnoreNonScreen (char**,int) ; 
 scalar_t__ LINES ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int arg_rest (char**) ; 
 TYPE_1__ dialog_state ; 
 int /*<<< orphan*/  dlg_auto_size (int /*<<< orphan*/ *,char*,int*,int*,int,int) ; 
 int /*<<< orphan*/  dlg_print_autowrap (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dlg_trim_string (char*) ; 
 int /*<<< orphan*/  dlg_ttysize (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int numeric_arg (char**,int) ; 
#define  o_print_text_only 129 
#define  o_print_text_size 128 
 int /*<<< orphan*/  optionString (char**,int*) ; 
 int /*<<< orphan*/  stdscr ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
PrintTextOnly(char **argv, int *offset, eOptions code)
{
    /* TODO - handle two optional numeric params */
    char *text;
    int height = 0;
    int width = 0;
    int height2 = 0;
    int width2 = 0;
    int next = arg_rest(argv + *offset);

    if (LINES <= 0 && COLS <= 0)
	dlg_ttysize(fileno(dialog_state.input), &LINES, &COLS);

    text = strdup(optionString(argv, offset));
    IgnoreNonScreen(argv, *offset);

    if (next >= 1) {
	next = MIN(next, 3);
	height = numeric_arg(argv, *offset + 1);
	if (next >= 2)
	    width = numeric_arg(argv, *offset + 2);
	*offset += next - 1;
    }

    dlg_trim_string(text);
    dlg_auto_size(NULL, text, &height2, &width2, height, width);

    switch (code) {
    case o_print_text_only:
	dialog_state.text_only = TRUE;
	dlg_print_autowrap(stdscr, text, height2, width2);
	dialog_state.text_only = FALSE;
	break;
    case o_print_text_size:
	fprintf(dialog_state.output, "%d %d\n",
		dialog_state.text_height,
		dialog_state.text_width);
	break;
    default:
	break;
    }
}