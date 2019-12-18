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
 int dlg_count_columns (char const*) ; 

void
dlg_button_sizes(const char **labels,
		 int vertical,
		 int *longest,
		 int *length)
{
    int n;

    *length = 0;
    *longest = 0;
    for (n = 0; labels[n] != 0; n++) {
	if (vertical) {
	    *length += 1;
	    *longest = 1;
	} else {
	    int len = dlg_count_columns(labels[n]);
	    if (len > *longest)
		*longest = len;
	    *length += len;
	}
    }
    /*
     * If we can, make all of the buttons the same size.  This is only optional
     * for buttons laid out horizontally.
     */
    if (*longest < 6 - (*longest & 1))
	*longest = 6 - (*longest & 1);
    if (!vertical)
	*length = *longest * n;
}