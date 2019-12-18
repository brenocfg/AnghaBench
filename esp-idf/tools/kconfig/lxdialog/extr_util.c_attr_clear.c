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
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void attr_clear(WINDOW * win, int height, int width, chtype attr)
{
	int i, j;

	wattrset(win, attr);
	for (i = 0; i < height; i++) {
		wmove(win, i, 0);
		for (j = 0; j < width; j++)
			waddch(win, ' ');
	}
	touchwin(win);
}