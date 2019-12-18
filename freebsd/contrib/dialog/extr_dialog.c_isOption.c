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
typedef  scalar_t__ strspn ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  OptionChars ; 
 int TRUE ; 
 int /*<<< orphan*/  UCH (char const) ; 
 char const** dialog_opts ; 
 int /*<<< orphan*/  dlg_exiterr (char*,char const*) ; 
 int /*<<< orphan*/  handle_leaks () ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static bool
isOption(const char *arg)
{
    bool result = FALSE;

    if (arg != 0) {
	if (dialog_opts != 0) {
	    int n;
	    for (n = 0; dialog_opts[n] != 0; ++n) {
		if (dialog_opts[n] == arg) {
		    result = TRUE;
		    break;
		}
	    }
	} else if (!strncmp(arg, "--", (size_t) 2) && isalpha(UCH(arg[2]))) {
	    if (strlen(arg) == (strspn) (arg, OptionChars)) {
		result = TRUE;
	    } else {
		handle_leaks();
		dlg_exiterr("Invalid option \"%s\"", arg);
	    }
	}
    }
    return result;
}