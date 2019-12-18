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
struct TYPE_2__ {int /*<<< orphan*/  nocollapse; scalar_t__ cr_wrap; scalar_t__ trim_whitespace; int /*<<< orphan*/  no_nl_expand; } ;

/* Variables and functions */
 char TAB ; 
 int /*<<< orphan*/  UCH (char) ; 
 TYPE_1__ dialog_vars ; 
 scalar_t__ isblank (int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  trim_blank (char*,char*) ; 

void
dlg_trim_string(char *s)
{
    char *base = s;
    char *p1;
    char *p = s;
    int has_newlines = !dialog_vars.no_nl_expand && (strstr(s, "\\n") != 0);

    while (*p != '\0') {
	if (*p == TAB && !dialog_vars.nocollapse)
	    *p = ' ';

	if (has_newlines) {	/* If prompt contains "\n" strings */
	    if (*p == '\\' && *(p + 1) == 'n') {
		*s++ = '\n';
		p += 2;
		p1 = p;
		/*
		 * Handle end of lines intelligently.  If '\n' follows "\n"
		 * then ignore the '\n'.  This eliminates the need to escape
		 * the '\n' character (no need to use "\n\").
		 */
		while (isblank(UCH(*p1)))
		    p1++;
		if (*p1 == '\n')
		    p = p1 + 1;
	    } else if (*p == '\n') {
		if (dialog_vars.cr_wrap)
		    *s++ = *p++;
		else {
		    /* Replace the '\n' with a space if cr_wrap is not set */
		    if (!trim_blank(base, p))
			*s++ = ' ';
		    p++;
		}
	    } else		/* If *p != '\n' */
		*s++ = *p++;
	} else if (dialog_vars.trim_whitespace) {
	    if (isblank(UCH(*p))) {
		if (!isblank(UCH(*(s - 1)))) {
		    *s++ = ' ';
		    p++;
		} else
		    p++;
	    } else if (*p == '\n') {
		if (dialog_vars.cr_wrap)
		    *s++ = *p++;
		else if (!isblank(UCH(*(s - 1)))) {
		    /* Strip '\n's if cr_wrap is not set. */
		    *s++ = ' ';
		    p++;
		} else
		    p++;
	    } else
		*s++ = *p++;
	} else {		/* If there are no "\n" strings */
	    if (isblank(UCH(*p)) && !dialog_vars.nocollapse) {
		if (!trim_blank(base, p))
		    *s++ = *p;
		p++;
	    } else
		*s++ = *p++;
	}
    }

    *s = '\0';
}