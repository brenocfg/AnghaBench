#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_1__ c_pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  pp_abstract_declarator (TYPE_1__*,scalar_t__) ; 
 int pp_c_flag_abstract ; 
 int /*<<< orphan*/  pp_c_identifier (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pp_c_left_paren (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_c_right_paren (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_declaration_specifiers (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  pp_declarator (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  pp_separate_with (TYPE_1__*,char) ; 
 scalar_t__ void_list_node ; 

void
pp_c_parameter_type_list (c_pretty_printer *pp, tree t)
{
  bool want_parm_decl = DECL_P (t) && !(pp->flags & pp_c_flag_abstract);
  tree parms = want_parm_decl ? DECL_ARGUMENTS (t) :  TYPE_ARG_TYPES (t);
  pp_c_left_paren (pp);
  if (parms == void_list_node)
    pp_c_identifier (pp, "void");
  else
    {
      bool first = true;
      for ( ; parms && parms != void_list_node; parms = TREE_CHAIN (parms))
	{
	  if (!first)
	    pp_separate_with (pp, ',');
	  first = false;
	  pp_declaration_specifiers
	    (pp, want_parm_decl ? parms : TREE_VALUE (parms));
	  if (want_parm_decl)
	    pp_declarator (pp, parms);
	  else
	    pp_abstract_declarator (pp, TREE_VALUE (parms));
	}
    }
  pp_c_right_paren (pp);
}