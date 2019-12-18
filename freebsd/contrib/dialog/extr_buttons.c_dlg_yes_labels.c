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
struct TYPE_2__ {scalar_t__ help_button; scalar_t__ extra_button; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 
 char** dlg_ok_labels () ; 
 char* my_help_label () ; 
 char* my_no_label () ; 
 char* my_yes_label () ; 

const char **
dlg_yes_labels(void)
{
    const char **result;

    if (dialog_vars.extra_button) {
	result = dlg_ok_labels();
    } else {
	static const char *labels[4];
	int n = 0;

	labels[n++] = my_yes_label();
	labels[n++] = my_no_label();
	if (dialog_vars.help_button)
	    labels[n++] = my_help_label();
	labels[n] = 0;

	result = labels;
    }

    return result;
}