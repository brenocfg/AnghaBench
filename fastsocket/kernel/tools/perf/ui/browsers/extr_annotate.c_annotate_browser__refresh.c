#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_browser {scalar_t__ height; } ;
struct TYPE_2__ {scalar_t__ jump_arrows; } ;

/* Variables and functions */
 int /*<<< orphan*/  HE_COLORSET_NORMAL ; 
 int /*<<< orphan*/  __ui_browser__vline (struct ui_browser*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  annotate_browser__draw_current_jump (struct ui_browser*) ; 
 TYPE_1__ annotate_browser__opts ; 
 int ui_browser__list_head_refresh (struct ui_browser*) ; 
 int /*<<< orphan*/  ui_browser__set_color (struct ui_browser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int annotate_browser__refresh(struct ui_browser *browser)
{
	int ret = ui_browser__list_head_refresh(browser);

	if (annotate_browser__opts.jump_arrows)
		annotate_browser__draw_current_jump(browser);

	ui_browser__set_color(browser, HE_COLORSET_NORMAL);
	__ui_browser__vline(browser, 7, 0, browser->height - 1);
	return ret;
}