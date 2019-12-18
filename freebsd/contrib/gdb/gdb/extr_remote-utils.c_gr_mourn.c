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

/* Variables and functions */
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  gr_clear_all_breakpoints () ; 
 int /*<<< orphan*/  gr_get_ops () ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ ) ; 

void
gr_mourn (void)
{
  gr_clear_all_breakpoints ();
  unpush_target (gr_get_ops ());
  generic_mourn_inferior ();
}