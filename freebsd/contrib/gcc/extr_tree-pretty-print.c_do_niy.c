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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 scalar_t__ EXPR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newline_and_indent (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 
 char** tree_code_name ; 

__attribute__((used)) static void
do_niy (pretty_printer *buffer, tree node)
{
  int i, len;

  pp_string (buffer, "<<< Unknown tree: ");
  pp_string (buffer, tree_code_name[(int) TREE_CODE (node)]);

  if (EXPR_P (node))
    {
      len = TREE_CODE_LENGTH (TREE_CODE (node));
      for (i = 0; i < len; ++i)
	{
	  newline_and_indent (buffer, 2);
	  dump_generic_node (buffer, TREE_OPERAND (node, i), 2, 0, false);
	}
    }

  pp_string (buffer, " >>>\n");
}