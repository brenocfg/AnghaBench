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
 int MIN_BUTTON ; 

int
dlg_next_button(const char **labels, int button)
{
    if (button < -1)
	button = -1;

    if (labels[button + 1] != 0) {
	++button;
    } else {
	button = MIN_BUTTON;
    }
    return button;
}