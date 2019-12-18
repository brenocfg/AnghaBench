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
struct TYPE_4__ {int output_count; char* separate_str; int /*<<< orphan*/  output; } ;
struct TYPE_3__ {char* input_result; int /*<<< orphan*/  separate_output; } ;

/* Variables and functions */
 char* DEFAULT_SEPARATE_STR ; 
#define  DLG_EXIT_EXTRA 131 
#define  DLG_EXIT_HELP 130 
#define  DLG_EXIT_ITEM_HELP 129 
#define  DLG_EXIT_OK 128 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 int FALSE ; 
 int TRUE ; 
 TYPE_2__ dialog_state ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
show_result(int ret)
{
    bool either = FALSE;

    switch (ret) {
    case DLG_EXIT_OK:
    case DLG_EXIT_EXTRA:
    case DLG_EXIT_HELP:
    case DLG_EXIT_ITEM_HELP:
	if ((dialog_state.output_count > 1) && !dialog_vars.separate_output) {
	    fputs((dialog_state.separate_str
		   ? dialog_state.separate_str
		   : DEFAULT_SEPARATE_STR),
		  dialog_state.output);
	    either = TRUE;
	}
	if (dialog_vars.input_result != 0
	    && dialog_vars.input_result[0] != '\0') {
	    fputs(dialog_vars.input_result, dialog_state.output);
	    DLG_TRACE(("# input_result:\n%s\n", dialog_vars.input_result));
	    either = TRUE;
	}
	if (either) {
	    fflush(dialog_state.output);
	}
	break;
    }
    return ret;
}