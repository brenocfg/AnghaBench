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
 int /*<<< orphan*/  COLS ; 
 int /*<<< orphan*/  LINES ; 
 int /*<<< orphan*/  dlg_attr_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_attr ; 
 int /*<<< orphan*/  stdscr ; 

void
dlg_clear(void)
{
    dlg_attr_clear(stdscr, LINES, COLS, screen_attr);
}