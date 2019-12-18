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
struct ui_browser {scalar_t__ width; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEWT_COLORSET_ROOT ; 
 int /*<<< orphan*/  SLsmg_gotorc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slsmg_write_nstring (char const*,scalar_t__) ; 
 int /*<<< orphan*/  ui_browser__set_color (struct ui_browser*,int /*<<< orphan*/ ) ; 

void __ui_browser__show_title(struct ui_browser *browser, const char *title)
{
	SLsmg_gotorc(0, 0);
	ui_browser__set_color(browser, NEWT_COLORSET_ROOT);
	slsmg_write_nstring(title, browser->width + 1);
}