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
 int /*<<< orphan*/  __ui_browser__show_title (struct ui_browser*,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui__lock ; 

void ui_browser__show_title(struct ui_browser *browser, const char *title)
{
	pthread_mutex_lock(&ui__lock);
	__ui_browser__show_title(browser, title);
	pthread_mutex_unlock(&ui__lock);
}