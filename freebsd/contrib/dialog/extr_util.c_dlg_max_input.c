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
struct TYPE_2__ {int max_input; } ;

/* Variables and functions */
 int MAX_LEN ; 
 TYPE_1__ dialog_vars ; 

int
dlg_max_input(int max_len)
{
    if (dialog_vars.max_input != 0 && dialog_vars.max_input < MAX_LEN)
	max_len = dialog_vars.max_input;

    return max_len;
}