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
struct TYPE_2__ {int has_children; } ;
struct hist_entry {int init_have_children; int /*<<< orphan*/  sorted_chain; TYPE_1__ ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain__init_have_children (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hist_entry__init_have_children(struct hist_entry *he)
{
	if (!he->init_have_children) {
		he->ms.has_children = !RB_EMPTY_ROOT(&he->sorted_chain);
		callchain__init_have_children(&he->sorted_chain);
		he->init_have_children = true;
	}
}