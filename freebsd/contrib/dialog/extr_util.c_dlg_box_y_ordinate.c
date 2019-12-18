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
struct TYPE_2__ {int begin_set; int begin_y; } ;

/* Variables and functions */
 int SLINES ; 
 TYPE_1__ dialog_vars ; 

int
dlg_box_y_ordinate(int height)
{
    int y;

    if (dialog_vars.begin_set == 1) {
	y = dialog_vars.begin_y;
    } else {
	/* center dialog box on screen unless --begin-set */
	y = (SLINES - height) / 2;
    }
    return y;
}