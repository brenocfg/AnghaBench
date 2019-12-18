#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dialog; } ;
typedef  TYPE_1__ DIALOG_MIXEDGAUGE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int /*<<< orphan*/  dlg_del_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dlg_finish_mixedgauge(DIALOG_MIXEDGAUGE * dlg, int status)
{
    (void) wrefresh(dlg->dialog);
#ifdef KEY_RESIZE
    nodelay(stdscr, FALSE);
#endif
    curs_set(1);
    dlg_del_window(dlg->dialog);
    return status;
}