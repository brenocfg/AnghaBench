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
struct ui_browser {int navkeypressed; int index; int nr_entries; int top_idx; int height; int /*<<< orphan*/  (* seek ) (struct ui_browser*,int,int /*<<< orphan*/ ) ;scalar_t__ use_navkeypressed; int /*<<< orphan*/  helpline; int /*<<< orphan*/  title; } ;
typedef  int off_t ;

/* Variables and functions */
#define  K_DOWN 133 
#define  K_END 132 
#define  K_HOME 131 
#define  K_PGDN 130 
#define  K_PGUP 129 
 int K_RESIZE ; 
#define  K_UP 128 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SLsmg_refresh () ; 
 int __ui_browser__refresh (struct ui_browser*) ; 
 int /*<<< orphan*/  __ui_browser__show_title (struct ui_browser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ui_browser*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ui_browser*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ui_browser*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ui_browser*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ui_browser*,int,int /*<<< orphan*/ ) ; 
 int ui__getch (int) ; 
 int /*<<< orphan*/  ui__lock ; 
 int /*<<< orphan*/  ui__refresh_dimensions (int) ; 
 int /*<<< orphan*/  ui_browser__refresh_dimensions (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_browser__reset_index (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_helpline__puts (int /*<<< orphan*/ ) ; 

int ui_browser__run(struct ui_browser *browser, int delay_secs)
{
	int err, key;

	while (1) {
		off_t offset;

		pthread_mutex_lock(&ui__lock);
		err = __ui_browser__refresh(browser);
		SLsmg_refresh();
		pthread_mutex_unlock(&ui__lock);
		if (err < 0)
			break;

		key = ui__getch(delay_secs);

		if (key == K_RESIZE) {
			ui__refresh_dimensions(false);
			ui_browser__refresh_dimensions(browser);
			__ui_browser__show_title(browser, browser->title);
			ui_helpline__puts(browser->helpline);
			continue;
		}

		if (browser->use_navkeypressed && !browser->navkeypressed) {
			if (key == K_DOWN || key == K_UP ||
			    key == K_PGDN || key == K_PGUP ||
			    key == K_HOME || key == K_END ||
			    key == ' ') {
				browser->navkeypressed = true;
				continue;
			} else
				return key;
		}

		switch (key) {
		case K_DOWN:
			if (browser->index == browser->nr_entries - 1)
				break;
			++browser->index;
			if (browser->index == browser->top_idx + browser->height) {
				++browser->top_idx;
				browser->seek(browser, +1, SEEK_CUR);
			}
			break;
		case K_UP:
			if (browser->index == 0)
				break;
			--browser->index;
			if (browser->index < browser->top_idx) {
				--browser->top_idx;
				browser->seek(browser, -1, SEEK_CUR);
			}
			break;
		case K_PGDN:
		case ' ':
			if (browser->top_idx + browser->height > browser->nr_entries - 1)
				break;

			offset = browser->height;
			if (browser->index + offset > browser->nr_entries - 1)
				offset = browser->nr_entries - 1 - browser->index;
			browser->index += offset;
			browser->top_idx += offset;
			browser->seek(browser, +offset, SEEK_CUR);
			break;
		case K_PGUP:
			if (browser->top_idx == 0)
				break;

			if (browser->top_idx < browser->height)
				offset = browser->top_idx;
			else
				offset = browser->height;

			browser->index -= offset;
			browser->top_idx -= offset;
			browser->seek(browser, -offset, SEEK_CUR);
			break;
		case K_HOME:
			ui_browser__reset_index(browser);
			break;
		case K_END:
			offset = browser->height - 1;
			if (offset >= browser->nr_entries)
				offset = browser->nr_entries - 1;

			browser->index = browser->nr_entries - 1;
			browser->top_idx = browser->index - offset;
			browser->seek(browser, -offset, SEEK_END);
			break;
		default:
			return key;
		}
	}
	return -1;
}