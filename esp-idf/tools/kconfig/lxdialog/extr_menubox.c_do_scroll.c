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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scrollok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wscrl (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void do_scroll(WINDOW *win, int *scroll, int n)
{
	/* Scroll menu up */
	scrollok(win, TRUE);
	wscrl(win, n);
	scrollok(win, FALSE);
	*scroll = *scroll + n;
	wrefresh(win);
}