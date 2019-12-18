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
struct TYPE_2__ {int width; } ;
struct hist_browser {int /*<<< orphan*/  hists; TYPE_1__ b; } ;

/* Variables and functions */
 int hists__sort_list_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hist_browser__refresh_dimensions(struct hist_browser *browser)
{
	/* 3 == +/- toggle symbol before actual hist_entry rendering */
	browser->b.width = 3 + (hists__sort_list_width(browser->hists) +
			     sizeof("[k]"));
}