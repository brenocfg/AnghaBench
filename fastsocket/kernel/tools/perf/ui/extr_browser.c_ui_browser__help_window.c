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
struct ui_browser {int dummy; } ;

/* Variables and functions */
 int K_RESIZE ; 
 int ui__help_window (char const*) ; 
 int /*<<< orphan*/  ui_browser__handle_resize (struct ui_browser*) ; 

int ui_browser__help_window(struct ui_browser *browser, const char *text)
{
	int key;

	while ((key = ui__help_window(text)) == K_RESIZE)
		ui_browser__handle_resize(browser);

	return key;
}