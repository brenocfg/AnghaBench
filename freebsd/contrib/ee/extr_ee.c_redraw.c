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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_win ; 
 scalar_t__ info_window ; 
 int /*<<< orphan*/  midscreen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paint_info_win () ; 
 int /*<<< orphan*/  point ; 
 int /*<<< orphan*/  scr_vert ; 
 int /*<<< orphan*/  text_win ; 

void 
redraw()
{
	if (info_window)
        {
                clearok(info_win, TRUE);
        	paint_info_win();
        }
        else
		clearok(text_win, TRUE);
	midscreen(scr_vert, point);
}