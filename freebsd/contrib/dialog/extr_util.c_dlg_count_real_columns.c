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
struct TYPE_2__ {scalar_t__ colors; } ;

/* Variables and functions */
 scalar_t__ ESCAPE_LEN ; 
 TYPE_1__ dialog_vars ; 
 int dlg_count_columns (char const*) ; 
 scalar_t__ isOurEscape (char const*) ; 

int
dlg_count_real_columns(const char *text)
{
    int result = 0;
    if (*text) {
	result = dlg_count_columns(text);
	if (result && dialog_vars.colors) {
	    int hidden = 0;
	    while (*text) {
		if (dialog_vars.colors && isOurEscape(text)) {
		    hidden += ESCAPE_LEN;
		    text += ESCAPE_LEN;
		} else {
		    ++text;
		}
	    }
	    result -= hidden;
	}
    }
    return result;
}