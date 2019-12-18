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
struct hists {int /*<<< orphan*/ * symbol_filter_str; } ;
struct TYPE_4__ {TYPE_1__* sym; } ;
struct hist_entry {int filtered; TYPE_2__ ms; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HIST_FILTER__SYMBOL ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hists__filter_entry_by_symbol(struct hists *hists,
					  struct hist_entry *he)
{
	if (hists->symbol_filter_str != NULL &&
	    (!he->ms.sym || strstr(he->ms.sym->name,
				   hists->symbol_filter_str) == NULL)) {
		he->filtered |= (1 << HIST_FILTER__SYMBOL);
		return true;
	}

	return false;
}