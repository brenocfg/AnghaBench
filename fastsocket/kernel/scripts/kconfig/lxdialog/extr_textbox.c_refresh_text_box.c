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
 int /*<<< orphan*/  print_page (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  print_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void refresh_text_box(WINDOW *dialog, WINDOW *box, int boxh, int boxw,
							  int cur_y, int cur_x)
{
	print_page(box, boxh, boxw);
	print_position(dialog);
	wmove(dialog, cur_y, cur_x);	/* Restore cursor position */
	wrefresh(dialog);
}