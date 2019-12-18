#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int dlg_count_columns (char*) ; 

int
dlg_calc_listw(int item_no, char **items, int group)
{
    int n, i, len1 = 0, len2 = 0;
    for (i = 0; i < (item_no * group); i += group) {
	if ((n = dlg_count_columns(items[i])) > len1)
	    len1 = n;
	if ((n = dlg_count_columns(items[i + 1])) > len2)
	    len2 = n;
    }
    return len1 + len2;
}