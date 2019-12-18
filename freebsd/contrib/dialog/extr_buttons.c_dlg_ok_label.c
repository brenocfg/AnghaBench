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
 char* my_extra_label () ; 
 char* my_help_label () ; 
 char* my_ok_label () ; 

const char **
dlg_ok_label(void)
{
    static const char *labels[4];
    int n = 0;

    labels[n++] = my_ok_label();
    if (dialog_vars.extra_button)
	labels[n++] = my_extra_label();
    if (dialog_vars.help_button)
	labels[n++] = my_help_label();
    labels[n] = 0;
    return labels;
}