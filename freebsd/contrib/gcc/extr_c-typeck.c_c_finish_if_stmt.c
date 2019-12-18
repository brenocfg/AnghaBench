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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
#define  BIND_EXPR 132 
 int /*<<< orphan*/ * BIND_EXPR_BODY (int /*<<< orphan*/ *) ; 
#define  COND_EXPR 131 
 scalar_t__ COND_EXPR_ELSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPT_Wparentheses ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  STATEMENT_LIST 130 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  TRY_CATCH_EXPR 129 
#define  TRY_FINALLY_EXPR 128 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  empty_body_warning (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * expr_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  void_type_node ; 
 scalar_t__ warn_parentheses ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
c_finish_if_stmt (location_t if_locus, tree cond, tree then_block,
		  tree else_block, bool nested_if)
{
  tree stmt;

  /* Diagnose an ambiguous else if if-then-else is nested inside if-then.  */
  if (warn_parentheses && nested_if && else_block == NULL)
    {
      tree inner_if = then_block;

      /* We know from the grammar productions that there is an IF nested
	 within THEN_BLOCK.  Due to labels and c99 conditional declarations,
	 it might not be exactly THEN_BLOCK, but should be the last
	 non-container statement within.  */
      while (1)
	switch (TREE_CODE (inner_if))
	  {
	  case COND_EXPR:
	    goto found;
	  case BIND_EXPR:
	    inner_if = BIND_EXPR_BODY (inner_if);
	    break;
	  case STATEMENT_LIST:
	    inner_if = expr_last (then_block);
	    break;
	  case TRY_FINALLY_EXPR:
	  case TRY_CATCH_EXPR:
	    inner_if = TREE_OPERAND (inner_if, 0);
	    break;
	  default:
	    gcc_unreachable ();
	  }
    found:

      if (COND_EXPR_ELSE (inner_if))
	 warning (OPT_Wparentheses,
		  "%Hsuggest explicit braces to avoid ambiguous %<else%>",
		  &if_locus);
    }

  empty_body_warning (then_block, else_block);

  stmt = build3 (COND_EXPR, void_type_node, cond, then_block, else_block);
  SET_EXPR_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}