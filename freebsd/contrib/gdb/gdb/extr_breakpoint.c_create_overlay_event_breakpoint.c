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
struct minimal_symbol {int dummy; } ;
struct breakpoint {int /*<<< orphan*/  enable_state; int /*<<< orphan*/  addr_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  bp_disabled ; 
 int /*<<< orphan*/  bp_enabled ; 
 int /*<<< orphan*/  bp_overlay_event ; 
 struct breakpoint* create_internal_breakpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol_text (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ overlay_debugging ; 
 int overlay_events_enabled ; 
 scalar_t__ ovly_auto ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
create_overlay_event_breakpoint (char *func_name)
{
  struct breakpoint *b;
  struct minimal_symbol *m;

  if ((m = lookup_minimal_symbol_text (func_name, NULL)) == NULL)
    return;
 
  b = create_internal_breakpoint (SYMBOL_VALUE_ADDRESS (m), 
				  bp_overlay_event);
  b->addr_string = xstrdup (func_name);

  if (overlay_debugging == ovly_auto)
    {
      b->enable_state = bp_enabled;
      overlay_events_enabled = 1;
    }
  else 
    {
      b->enable_state = bp_disabled;
      overlay_events_enabled = 0;
    }
}