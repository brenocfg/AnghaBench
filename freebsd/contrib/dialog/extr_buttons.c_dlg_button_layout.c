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
 int COLS ; 
 int MARGIN ; 
 scalar_t__ dlg_button_count (char const**) ; 
 int /*<<< orphan*/  dlg_button_x_step (char const**,int,int*,int*,int*) ; 

void
dlg_button_layout(const char **labels, int *limit)
{
    int width = 1;
    int gap, margin, step;

    if (labels != 0 && dlg_button_count(labels)) {
	while (!dlg_button_x_step(labels, width, &gap, &margin, &step))
	    ++width;
	width += (4 * MARGIN);
	if (width > COLS)
	    width = COLS;
	if (width > *limit)
	    *limit = width;
    }
}