#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hists {int dummy; } ;
struct TYPE_8__ {int use_navkeypressed; int /*<<< orphan*/  seek; int /*<<< orphan*/  refresh; } ;
struct hist_browser {int /*<<< orphan*/  has_symbols; TYPE_3__ b; struct hists* hists; } ;
struct TYPE_7__ {int /*<<< orphan*/ * next; } ;
struct TYPE_10__ {TYPE_2__ list; } ;
struct TYPE_6__ {int /*<<< orphan*/ * next; } ;
struct TYPE_9__ {TYPE_1__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_browser__refresh ; 
 int sort__branch_mode ; 
 TYPE_5__ sort_sym ; 
 TYPE_4__ sort_sym_from ; 
 int /*<<< orphan*/  ui_browser__hists_seek ; 
 struct hist_browser* zalloc (int) ; 

__attribute__((used)) static struct hist_browser *hist_browser__new(struct hists *hists)
{
	struct hist_browser *browser = zalloc(sizeof(*browser));

	if (browser) {
		browser->hists = hists;
		browser->b.refresh = hist_browser__refresh;
		browser->b.seek = ui_browser__hists_seek;
		browser->b.use_navkeypressed = true;
		if (sort__branch_mode == 1)
			browser->has_symbols = sort_sym_from.list.next != NULL;
		else
			browser->has_symbols = sort_sym.list.next != NULL;
	}

	return browser;
}