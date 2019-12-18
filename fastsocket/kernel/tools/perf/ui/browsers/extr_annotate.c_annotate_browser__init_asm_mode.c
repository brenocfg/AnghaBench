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
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;
struct annotate_browser {int /*<<< orphan*/  nr_asm_entries; TYPE_1__ b; } ;

/* Variables and functions */
 int /*<<< orphan*/  ui_browser__reset_index (TYPE_1__*) ; 

__attribute__((used)) static void annotate_browser__init_asm_mode(struct annotate_browser *browser)
{
	ui_browser__reset_index(&browser->b);
	browser->b.nr_entries = browser->nr_asm_entries;
}