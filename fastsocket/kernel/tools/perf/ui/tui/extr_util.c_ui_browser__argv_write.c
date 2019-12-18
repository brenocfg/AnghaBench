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
struct ui_browser {int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  HE_COLORSET_NORMAL ; 
 int /*<<< orphan*/  HE_COLORSET_SELECTED ; 
 int /*<<< orphan*/  slsmg_write_nstring (char*,int /*<<< orphan*/ ) ; 
 int ui_browser__is_current_entry (struct ui_browser*,int) ; 
 int /*<<< orphan*/  ui_browser__set_color (struct ui_browser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ui_browser__argv_write(struct ui_browser *browser,
				   void *entry, int row)
{
	char **arg = entry;
	bool current_entry = ui_browser__is_current_entry(browser, row);

	ui_browser__set_color(browser, current_entry ? HE_COLORSET_SELECTED :
						       HE_COLORSET_NORMAL);
	slsmg_write_nstring(*arg, browser->width);
}