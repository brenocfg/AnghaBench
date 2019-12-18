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
 int dlg_find_index (int const*,int,int) ; 
 int* dlg_index_columns (char const*) ; 
 int* dlg_index_wchars (char const*) ; 

__attribute__((used)) static void
compute_edit_offset(const char *string,
		    int chr_offset,
		    int x_last,
		    int *p_dpy_column,
		    int *p_scroll_amt)
{
    const int *cols = dlg_index_columns(string);
    const int *indx = dlg_index_wchars(string);
    int limit = dlg_count_wchars(string);
    int offset = dlg_find_index(indx, limit, chr_offset);
    int offset2;
    int dpy_column;
    int n;

    for (n = offset2 = 0; n <= offset; ++n) {
	if ((cols[offset] - cols[n]) < x_last
	    && (offset == limit || (cols[offset + 1] - cols[n]) < x_last)) {
	    offset2 = n;
	    break;
	}
    }

    dpy_column = cols[offset] - cols[offset2];

    if (p_dpy_column != 0)
	*p_dpy_column = dpy_column;
    if (p_scroll_amt != 0)
	*p_scroll_amt = offset2;
}