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
 scalar_t__ dlg_ok_buttoncode (int) ; 

int
dlg_prev_ok_buttonindex(int current, int extra)
{
    int result = current - 1;

    if (result < extra) {
	for (result = 0; dlg_ok_buttoncode(result + 1) >= 0; ++result) {
	    ;
	}
    }
    return result;
}