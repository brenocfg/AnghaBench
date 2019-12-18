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
 int /*<<< orphan*/  dlg_finish_string (char const*) ; 
 int* dlg_index_columns (char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
dlg_count_columns(const char *string)
{
    int result = 0;
    int limit = dlg_count_wchars(string);
    if (limit > 0) {
	const int *cols = dlg_index_columns(string);
	result = cols[limit];
    } else {
	result = (int) strlen(string);
    }
    dlg_finish_string(string);
    return result;
}