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
typedef  scalar_t__ strchr ;
struct TYPE_2__ {scalar_t__ single_quoted; } ;

/* Variables and functions */
 char* FIX_DOUBLE ; 
 char* FIX_SINGLE ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_add_result (char const*) ; 
 scalar_t__ must_quote (char*) ; 
 char* quote_delimiter () ; 

void
dlg_add_quoted(char *string)
{
    char temp[2];
    const char *my_quote = quote_delimiter();
    const char *must_fix = (dialog_vars.single_quoted
			    ? FIX_SINGLE
			    : FIX_DOUBLE);

    if (must_quote(string)) {
	temp[1] = '\0';
	dlg_add_result(my_quote);
	while (*string != '\0') {
	    temp[0] = *string++;
	    if ((strchr) (my_quote, *temp) || (strchr) (must_fix, *temp))
		dlg_add_result("\\");
	    dlg_add_result(temp);
	}
	dlg_add_result(my_quote);
    } else {
	dlg_add_result(string);
    }
}