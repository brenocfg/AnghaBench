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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  justify_text (int /*<<< orphan*/ *,char const*,int,int,int*,int*) ; 

void
dlg_print_autowrap(WINDOW *win, const char *prompt, int height, int width)
{
    justify_text(win, prompt,
		 height,
		 width,
		 (int *) 0, (int *) 0);
}