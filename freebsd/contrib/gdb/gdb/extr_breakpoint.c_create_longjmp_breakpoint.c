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
struct breakpoint {int silent; int /*<<< orphan*/  addr_string; int /*<<< orphan*/  enable_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  bp_disabled ; 
 int /*<<< orphan*/  bp_longjmp ; 
 int /*<<< orphan*/  bp_longjmp_resume ; 
 struct breakpoint* create_internal_breakpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol_text (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
create_longjmp_breakpoint (char *func_name)
{
  struct breakpoint *b;
  struct minimal_symbol *m;

  if (func_name == NULL)
    b = create_internal_breakpoint (0, bp_longjmp_resume);
  else
    {
      if ((m = lookup_minimal_symbol_text (func_name, NULL)) == NULL)
	return;
 
      b = create_internal_breakpoint (SYMBOL_VALUE_ADDRESS (m), bp_longjmp);
    }

  b->enable_state = bp_disabled;
  b->silent = 1;
  if (func_name)
    b->addr_string = xstrdup (func_name);
}