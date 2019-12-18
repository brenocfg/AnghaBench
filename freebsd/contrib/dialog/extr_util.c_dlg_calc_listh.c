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
struct TYPE_2__ {int begin_y; scalar_t__ begin_set; } ;

/* Variables and functions */
 int SLINES ; 
 TYPE_1__ dialog_vars ; 

void
dlg_calc_listh(int *height, int *list_height, int item_no)
{
    /* calculate new height and list_height */
    int rows = SLINES - (dialog_vars.begin_set ? dialog_vars.begin_y : 0);
    if (rows - (*height) > 0) {
	if (rows - (*height) > item_no)
	    *list_height = item_no;
	else
	    *list_height = rows - (*height);
    }
    (*height) += (*list_height);
}