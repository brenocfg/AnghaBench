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
 scalar_t__ dlg_isupper (int) ; 
 int string_to_char (char const**) ; 

int
dlg_button_to_char(const char *label)
{
    int cmp = -1;

    while (*label != 0) {
	cmp = string_to_char(&label);
	if (dlg_isupper(cmp)) {
	    break;
	}
    }
    return cmp;
}