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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
dump_function_declaration (pretty_printer *buffer, tree node,
			   int spc, int flags)
{
  bool wrote_arg = false;
  tree arg;

  pp_space (buffer);
  pp_character (buffer, '(');

  /* Print the argument types.  The last element in the list is a VOID_TYPE.
     The following avoids printing the last element.  */
  arg = TYPE_ARG_TYPES (node);
  while (arg && TREE_CHAIN (arg) && arg != error_mark_node)
    {
      wrote_arg = true;
      dump_generic_node (buffer, TREE_VALUE (arg), spc, flags, false);
      arg = TREE_CHAIN (arg);
      if (TREE_CHAIN (arg) && TREE_CODE (TREE_CHAIN (arg)) == TREE_LIST)
	{
	  pp_character (buffer, ',');
	  pp_space (buffer);
	}
    }

  if (!wrote_arg)
    pp_string (buffer, "void");

  pp_character (buffer, ')');
}