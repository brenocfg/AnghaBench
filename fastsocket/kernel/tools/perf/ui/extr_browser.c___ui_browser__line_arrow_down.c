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
typedef  scalar_t__ u64 ;
struct ui_browser {scalar_t__ top_idx; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLSMG_HLINE_CHAR ; 
 int /*<<< orphan*/  SLSMG_LLCORN_CHAR ; 
 int /*<<< orphan*/  SLSMG_RARROW_CHAR ; 
 int /*<<< orphan*/  SLSMG_ULCORN_CHAR ; 
 int /*<<< orphan*/  SLsmg_draw_hline (int) ; 
 int /*<<< orphan*/  SLsmg_draw_vline (unsigned int) ; 
 int /*<<< orphan*/  SLsmg_set_char_set (int) ; 
 int /*<<< orphan*/  SLsmg_write_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_browser__gotorc (struct ui_browser*,unsigned int,unsigned int) ; 

__attribute__((used)) static void __ui_browser__line_arrow_down(struct ui_browser *browser,
					  unsigned int column,
					  u64 start, u64 end)
{
	unsigned int row, end_row;

	SLsmg_set_char_set(1);

	if (start >= browser->top_idx) {
		row = start - browser->top_idx;
		ui_browser__gotorc(browser, row, column);
		SLsmg_write_char(SLSMG_ULCORN_CHAR);
		ui_browser__gotorc(browser, row, column + 1);
		SLsmg_draw_hline(2);

		if (row++ == 0)
			goto out;
	} else
		row = 0;

	if (end >= browser->top_idx + browser->height)
		end_row = browser->height - 1;
	else
		end_row = end - browser->top_idx;;

	ui_browser__gotorc(browser, row, column);
	SLsmg_draw_vline(end_row - row + 1);

	ui_browser__gotorc(browser, end_row, column);
	if (end < browser->top_idx + browser->height) {
		SLsmg_write_char(SLSMG_LLCORN_CHAR);
		ui_browser__gotorc(browser, end_row, column + 1);
		SLsmg_write_char(SLSMG_HLINE_CHAR);
		ui_browser__gotorc(browser, end_row, column + 2);
		SLsmg_write_char(SLSMG_RARROW_CHAR);
	}
out:
	SLsmg_set_char_set(0);
}