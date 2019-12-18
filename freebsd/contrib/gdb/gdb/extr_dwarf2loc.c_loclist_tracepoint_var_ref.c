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
struct dwarf2_loclist_baton {int dummy; } ;
struct axs_value {int dummy; } ;
struct agent_expr {int /*<<< orphan*/  scope; } ;

/* Variables and functions */
 struct dwarf2_loclist_baton* SYMBOL_LOCATION_BATON (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_NATURAL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  dwarf2_tracepoint_var_ref (struct symbol*,struct agent_expr*,struct axs_value*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 unsigned char* find_location_expression (struct dwarf2_loclist_baton*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
loclist_tracepoint_var_ref (struct symbol * symbol, struct agent_expr * ax,
			    struct axs_value * value)
{
  struct dwarf2_loclist_baton *dlbaton = SYMBOL_LOCATION_BATON (symbol);
  unsigned char *data;
  size_t size;

  data = find_location_expression (dlbaton, &size, ax->scope);
  if (data == NULL)
    error ("Variable \"%s\" is not available.", SYMBOL_NATURAL_NAME (symbol));

  dwarf2_tracepoint_var_ref (symbol, ax, value, data, size);
}