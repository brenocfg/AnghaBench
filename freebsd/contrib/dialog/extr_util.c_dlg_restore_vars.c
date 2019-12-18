#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* input_result; unsigned int input_length; } ;
typedef  TYPE_1__ DIALOG_VARS ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 

void
dlg_restore_vars(DIALOG_VARS * vars)
{
    char *save_result = dialog_vars.input_result;
    unsigned save_length = dialog_vars.input_length;

    dialog_vars = *vars;
    dialog_vars.input_result = save_result;
    dialog_vars.input_length = save_length;
}