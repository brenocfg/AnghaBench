#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nr_entries; } ;
struct hist_browser {TYPE_1__ b; TYPE_2__* hists; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__set_folding (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ui_browser__reset_index (TYPE_1__*) ; 

__attribute__((used)) static void hist_browser__set_folding(struct hist_browser *browser, bool unfold)
{
	hists__set_folding(browser->hists, unfold);
	browser->b.nr_entries = browser->hists->nr_entries;
	/* Go to the start, we may be way after valid entries after a collapse */
	ui_browser__reset_index(&browser->b);
}