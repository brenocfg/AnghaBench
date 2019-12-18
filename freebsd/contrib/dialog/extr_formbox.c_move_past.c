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
 scalar_t__ ERR ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 scalar_t__ wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
move_past(WINDOW *win, int y, int x)
{
    if (wmove(win, y, x) == ERR)
	wmove(win, y, getmaxx(win) - 1);
}