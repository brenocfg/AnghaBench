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

int
dlg_find_index(const int *list, int limit, int to_find)
{
    int result;
    for (result = 0; result <= limit; ++result) {
	if (to_find == list[result]
	    || result == limit
	    || ((result < limit) && (to_find < list[result + 1]))) {
	    break;
	}
    }
    return result;
}