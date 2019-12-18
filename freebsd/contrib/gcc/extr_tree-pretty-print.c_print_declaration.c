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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ CODE_CONTAINS_STRUCT (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ASSEMBLER_NAME (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 scalar_t__ DECL_HARD_REGISTER (scalar_t__) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ DECL_REGISTER (scalar_t__) ; 
 scalar_t__ DECL_VALUE_EXPR (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  INDENT (int) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_PUBLIC (scalar_t__) ; 
 scalar_t__ TREE_STATIC (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TS_DECL_WRTL ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  dump_array_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dump_decl_name (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  dump_function_declaration (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
print_declaration (pretty_printer *buffer, tree t, int spc, int flags)
{
  INDENT (spc);

  if (TREE_CODE (t) == TYPE_DECL)
    pp_string (buffer, "typedef ");

  if (CODE_CONTAINS_STRUCT (TREE_CODE (t), TS_DECL_WRTL) && DECL_REGISTER (t))
    pp_string (buffer, "register ");

  if (TREE_PUBLIC (t) && DECL_EXTERNAL (t))
    pp_string (buffer, "extern ");
  else if (TREE_STATIC (t))
    pp_string (buffer, "static ");

  /* Print the type and name.  */
  if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
    {
      tree tmp;

      /* Print array's type.  */
      tmp = TREE_TYPE (t);
      while (TREE_CODE (TREE_TYPE (tmp)) == ARRAY_TYPE)
	tmp = TREE_TYPE (tmp);
      dump_generic_node (buffer, TREE_TYPE (tmp), spc, flags, false);

      /* Print variable's name.  */
      pp_space (buffer);
      dump_generic_node (buffer, t, spc, flags, false);

      /* Print the dimensions.  */
      tmp = TREE_TYPE (t);
      while (TREE_CODE (tmp) == ARRAY_TYPE)
	{
	  dump_array_domain (buffer, TYPE_DOMAIN (tmp), spc, flags);
	  tmp = TREE_TYPE (tmp);
	}
    }
  else if (TREE_CODE (t) == FUNCTION_DECL)
    {
      dump_generic_node (buffer, TREE_TYPE (TREE_TYPE (t)), spc, flags, false);
      pp_space (buffer);
      dump_decl_name (buffer, t, flags);
      dump_function_declaration (buffer, TREE_TYPE (t), spc, flags);
    }
  else
    {
      /* Print type declaration.  */
      dump_generic_node (buffer, TREE_TYPE (t), spc, flags, false);

      /* Print variable's name.  */
      pp_space (buffer);
      dump_generic_node (buffer, t, spc, flags, false);
    }

  if (TREE_CODE (t) == VAR_DECL && DECL_HARD_REGISTER (t))
    {
      pp_string (buffer, " __asm__ ");
      pp_character (buffer, '(');
      dump_generic_node (buffer, DECL_ASSEMBLER_NAME (t), spc, flags, false);
      pp_character (buffer, ')');
    }

  /* The initial value of a function serves to determine wether the function
     is declared or defined.  So the following does not apply to function
     nodes.  */
  if (TREE_CODE (t) != FUNCTION_DECL)
    {
      /* Print the initial value.  */
      if (DECL_INITIAL (t))
	{
	  pp_space (buffer);
	  pp_character (buffer, '=');
	  pp_space (buffer);
	  dump_generic_node (buffer, DECL_INITIAL (t), spc, flags, false);
	}
    }

  if (TREE_CODE (t) == VAR_DECL && DECL_HAS_VALUE_EXPR_P (t))
    {
      pp_string (buffer, " [value-expr: ");
      dump_generic_node (buffer, DECL_VALUE_EXPR (t), spc, flags, false);
      pp_character (buffer, ']');
    }

  pp_character (buffer, ';');
}