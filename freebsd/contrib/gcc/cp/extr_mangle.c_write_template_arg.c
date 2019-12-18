#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {int need_abi_warning; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int CONST_DECL ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 TYPE_1__ G ; 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ NOP_EXPR ; 
 int PTRMEM_CST ; 
 scalar_t__ REFERENCE_TYPE ; 
 int TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int TREE_LIST ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ abi_version_at_least (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ tcc_constant ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_encoding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string (char*) ; 
 int /*<<< orphan*/  write_template_arg_literal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_template_template_arg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_template_arg (tree node)
{
  enum tree_code code = TREE_CODE (node);

  MANGLE_TRACE_TREE ("template-arg", node);

  /* A template template parameter's argument list contains TREE_LIST
     nodes of which the value field is the actual argument.  */
  if (code == TREE_LIST)
    {
      node = TREE_VALUE (node);
      /* If it's a decl, deal with its type instead.  */
      if (DECL_P (node))
	{
	  node = TREE_TYPE (node);
	  code = TREE_CODE (node);
	}
    }

  if (TREE_CODE (node) == NOP_EXPR
      && TREE_CODE (TREE_TYPE (node)) == REFERENCE_TYPE)
    {
      /* Template parameters can be of reference type. To maintain
	 internal consistency, such arguments use a conversion from
	 address of object to reference type.  */
      gcc_assert (TREE_CODE (TREE_OPERAND (node, 0)) == ADDR_EXPR);
      if (abi_version_at_least (2))
	node = TREE_OPERAND (TREE_OPERAND (node, 0), 0);
      else
	G.need_abi_warning = 1;
    }

  if (TYPE_P (node))
    write_type (node);
  else if (code == TEMPLATE_DECL)
    /* A template appearing as a template arg is a template template arg.  */
    write_template_template_arg (node);
  else if ((TREE_CODE_CLASS (code) == tcc_constant && code != PTRMEM_CST)
	   || (abi_version_at_least (2) && code == CONST_DECL))
    write_template_arg_literal (node);
  else if (DECL_P (node))
    {
      /* Until ABI version 2, non-type template arguments of
	 enumeration type were mangled using their names.  */
      if (code == CONST_DECL && !abi_version_at_least (2))
	G.need_abi_warning = 1;
      write_char ('L');
      /* Until ABI version 3, the underscore before the mangled name
	 was incorrectly omitted.  */
      if (!abi_version_at_least (3))
	{
	  G.need_abi_warning = 1;
	  write_char ('Z');
	}
      else
	write_string ("_Z");
      write_encoding (node);
      write_char ('E');
    }
  else
    {
      /* Template arguments may be expressions.  */
      write_char ('X');
      write_expression (node);
      write_char ('E');
    }
}