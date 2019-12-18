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
typedef  union type_stack_elt {int dummy; } type_stack_elt ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_GDBARCH_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_parse () ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  deprecated_register_gdbarch_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  expressiondebug ; 
 int /*<<< orphan*/  msym_data_symbol_type ; 
 int /*<<< orphan*/  msym_text_symbol_type ; 
 int /*<<< orphan*/  msym_unknown_symbol_type ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  showdebuglist ; 
 union type_stack_elt* type_stack ; 
 scalar_t__ type_stack_depth ; 
 int type_stack_size ; 
 int /*<<< orphan*/  var_zinteger ; 
 scalar_t__ xmalloc (int) ; 

void
_initialize_parse (void)
{
  type_stack_size = 80;
  type_stack_depth = 0;
  type_stack = (union type_stack_elt *)
    xmalloc (type_stack_size * sizeof (*type_stack));

  build_parse ();

  /* FIXME - For the moment, handle types by swapping them in and out.
     Should be using the per-architecture data-pointer and a large
     struct. */
  DEPRECATED_REGISTER_GDBARCH_SWAP (msym_text_symbol_type);
  DEPRECATED_REGISTER_GDBARCH_SWAP (msym_data_symbol_type);
  DEPRECATED_REGISTER_GDBARCH_SWAP (msym_unknown_symbol_type);
  deprecated_register_gdbarch_swap (NULL, 0, build_parse);

  add_show_from_set (
	    add_set_cmd ("expression", class_maintenance, var_zinteger,
			 (char *) &expressiondebug,
			 "Set expression debugging.\n\
When non-zero, the internal representation of expressions will be printed.",
			 &setdebuglist),
		      &showdebuglist);
}