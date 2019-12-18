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
struct symbol {int dummy; } ;
struct dwarf2_locexpr_baton {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct axs_value {int dummy; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 struct dwarf2_locexpr_baton* SYMBOL_LOCATION_BATON (struct symbol*) ; 
 int /*<<< orphan*/  dwarf2_tracepoint_var_ref (struct symbol*,struct agent_expr*,struct axs_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
locexpr_tracepoint_var_ref (struct symbol * symbol, struct agent_expr * ax,
			    struct axs_value * value)
{
  struct dwarf2_locexpr_baton *dlbaton = SYMBOL_LOCATION_BATON (symbol);

  dwarf2_tracepoint_var_ref (symbol, ax, value, dlbaton->data, dlbaton->size);
}