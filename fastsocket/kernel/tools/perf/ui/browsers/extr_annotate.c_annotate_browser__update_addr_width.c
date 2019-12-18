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
struct annotate_browser {scalar_t__ jumps_width; int /*<<< orphan*/  addr_width; int /*<<< orphan*/  target_width; int /*<<< orphan*/  max_addr_width; int /*<<< orphan*/  min_addr_width; } ;
struct TYPE_2__ {scalar_t__ show_nr_jumps; scalar_t__ use_offset; } ;

/* Variables and functions */
 TYPE_1__ annotate_browser__opts ; 

__attribute__((used)) static void annotate_browser__update_addr_width(struct annotate_browser *browser)
{
	if (annotate_browser__opts.use_offset)
		browser->target_width = browser->min_addr_width;
	else
		browser->target_width = browser->max_addr_width;

	browser->addr_width = browser->target_width;

	if (annotate_browser__opts.show_nr_jumps)
		browser->addr_width += browser->jumps_width + 1;
}