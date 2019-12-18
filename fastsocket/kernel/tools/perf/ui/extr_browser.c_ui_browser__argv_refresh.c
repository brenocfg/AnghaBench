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
struct ui_browser {unsigned int top_idx; unsigned int nr_entries; unsigned int height; int /*<<< orphan*/  (* write ) (struct ui_browser*,char**,unsigned int) ;int /*<<< orphan*/  (* filter ) (struct ui_browser*,char*) ;int /*<<< orphan*/ * top; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_browser*,char*) ; 
 int /*<<< orphan*/  stub2 (struct ui_browser*,char**,unsigned int) ; 
 int /*<<< orphan*/  ui_browser__gotorc (struct ui_browser*,unsigned int,int /*<<< orphan*/ ) ; 

unsigned int ui_browser__argv_refresh(struct ui_browser *browser)
{
	unsigned int row = 0, idx = browser->top_idx;
	char **pos;

	if (browser->top == NULL)
		browser->top = browser->entries;

	pos = (char **)browser->top;
	while (idx < browser->nr_entries) {
		if (!browser->filter || !browser->filter(browser, *pos)) {
			ui_browser__gotorc(browser, row, 0);
			browser->write(browser, pos, row);
			if (++row == browser->height)
				break;
		}

		++idx;
		++pos;
	}

	return row;
}