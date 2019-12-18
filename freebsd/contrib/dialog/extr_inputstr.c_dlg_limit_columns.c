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
 int dlg_count_wchars (char const*) ; 
 int* dlg_index_columns (char const*) ; 

int
dlg_limit_columns(const char *string, int limit, int offset)
{
    const int *cols = dlg_index_columns(string);
    int result = dlg_count_wchars(string);

    while (result > 0 && (cols[result] - cols[offset]) > limit)
	--result;
    return result;
}