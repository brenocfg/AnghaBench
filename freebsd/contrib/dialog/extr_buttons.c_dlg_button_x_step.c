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
 int /*<<< orphan*/  FALSE ; 
 int dlg_button_count (char const**) ; 
 int /*<<< orphan*/  dlg_button_sizes (char const**,int /*<<< orphan*/ ,int*,int*) ; 

int
dlg_button_x_step(const char **labels, int limit, int *gap, int *margin, int *step)
{
    int count = dlg_button_count(labels);
    int longest;
    int length;
    int unused;
    int used;
    int result;

    *margin = 0;
    if (count != 0) {
	dlg_button_sizes(labels, FALSE, &longest, &length);
	used = (length + (count * 2));
	unused = limit - used;

	if ((*gap = unused / (count + 3)) <= 0) {
	    if ((*gap = unused / (count + 1)) <= 0)
		*gap = 1;
	    *margin = *gap;
	} else {
	    *margin = *gap * 2;
	}
	*step = *gap + (used + count - 1) / count;
	result = (*gap > 0) && (unused >= 0);
    } else {
	result = 0;
    }
    return result;
}