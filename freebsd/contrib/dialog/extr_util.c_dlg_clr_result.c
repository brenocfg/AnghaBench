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
struct TYPE_2__ {scalar_t__ input_result; scalar_t__ input_length; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void
dlg_clr_result(void)
{
    if (dialog_vars.input_length) {
	dialog_vars.input_length = 0;
	if (dialog_vars.input_result)
	    free(dialog_vars.input_result);
    }
    dialog_vars.input_result = 0;
}