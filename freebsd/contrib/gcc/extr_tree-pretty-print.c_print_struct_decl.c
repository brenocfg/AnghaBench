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
 int /*<<< orphan*/  INDENT (int) ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ QUAL_UNION_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_newline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_declaration (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

__attribute__((used)) static void
print_struct_decl (pretty_printer *buffer, tree node, int spc, int flags)
{
  /* Print the name of the structure.  */
  if (TYPE_NAME (node))
    {
      INDENT (spc);
      if (TREE_CODE (node) == RECORD_TYPE)
	pp_string (buffer, "struct ");
      else if ((TREE_CODE (node) == UNION_TYPE
		|| TREE_CODE (node) == QUAL_UNION_TYPE))
	pp_string (buffer, "union ");

      dump_generic_node (buffer, TYPE_NAME (node), spc, 0, false);
    }

  /* Print the contents of the structure.  */
  pp_newline (buffer);
  INDENT (spc);
  pp_character (buffer, '{');
  pp_newline (buffer);

  /* Print the fields of the structure.  */
  {
    tree tmp;
    tmp = TYPE_FIELDS (node);
    while (tmp)
      {
	/* Avoid to print recursively the structure.  */
	/* FIXME : Not implemented correctly...,
	   what about the case when we have a cycle in the contain graph? ...
	   Maybe this could be solved by looking at the scope in which the
	   structure was declared.  */
	if (TREE_TYPE (tmp) != node
	    || (TREE_CODE (TREE_TYPE (tmp)) == POINTER_TYPE
		&& TREE_TYPE (TREE_TYPE (tmp)) != node))
	  {
	    print_declaration (buffer, tmp, spc+2, flags);
	    pp_newline (buffer);
	  }
	tmp = TREE_CHAIN (tmp);
      }
  }
  INDENT (spc);
  pp_character (buffer, '}');
}