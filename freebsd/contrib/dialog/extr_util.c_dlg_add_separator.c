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
struct TYPE_2__ {char* output_separator; scalar_t__ separate_output; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_add_result (char const*) ; 

void
dlg_add_separator(void)
{
    const char *separator = (dialog_vars.separate_output) ? "\n" : " ";

    if (dialog_vars.output_separator)
	separator = dialog_vars.output_separator;

    dlg_add_result(separator);
}