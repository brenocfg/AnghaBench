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
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ stmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_LOCUS (scalar_t__) ; 
 scalar_t__ IS_EMPTY_STMT (scalar_t__) ; 
 int /*<<< orphan*/  OPT_Wextra ; 
 scalar_t__ STATEMENT_LIST ; 
 TYPE_1__* STATEMENT_LIST_TAIL (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ extra_warnings ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
empty_body_warning (tree inner_then, tree inner_else)
{
  if (extra_warnings)
    {
      if (TREE_CODE (inner_then) == STATEMENT_LIST
	  && STATEMENT_LIST_TAIL (inner_then))
	inner_then = STATEMENT_LIST_TAIL (inner_then)->stmt;

      if (inner_else && TREE_CODE (inner_else) == STATEMENT_LIST
	  && STATEMENT_LIST_TAIL (inner_else))
	inner_else = STATEMENT_LIST_TAIL (inner_else)->stmt;

      if (IS_EMPTY_STMT (inner_then) && !inner_else)
	warning (OPT_Wextra, "%Hempty body in an if-statement",
		 EXPR_LOCUS (inner_then));

      if (inner_else && IS_EMPTY_STMT (inner_else))
	warning (OPT_Wextra, "%Hempty body in an else-statement",
		 EXPR_LOCUS (inner_else));
   }
}