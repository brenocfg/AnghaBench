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
struct ui_browser {int /*<<< orphan*/  (* filter ) (struct ui_browser*,struct list_head*) ;struct list_head* entries; } ;
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_browser*,struct list_head*) ; 

__attribute__((used)) static struct list_head *
ui_browser__list_head_filter_entries(struct ui_browser *browser,
				     struct list_head *pos)
{
	do {
		if (!browser->filter || !browser->filter(browser, pos))
			return pos;
		pos = pos->next;
	} while (pos != browser->entries);

	return NULL;
}