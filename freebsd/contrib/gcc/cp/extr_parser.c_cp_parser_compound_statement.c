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
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  BCS_TRY_BLOCK ; 
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_statement_seq_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_mark_locals_volatile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
cp_parser_compound_statement (cp_parser *parser, tree in_statement_expr,
			      /* APPLE LOCAL radar 5982990 */
			      bool in_try, bool objc_sjlj_exceptions)
{
  tree compound_stmt;

  /* Consume the `{'.  */
  if (!cp_parser_require (parser, CPP_OPEN_BRACE, "`{'"))
    return error_mark_node;
  /* Begin the compound-statement.  */
  compound_stmt = begin_compound_stmt (in_try ? BCS_TRY_BLOCK : 0);
  /* Parse an (optional) statement-seq.  */
  cp_parser_statement_seq_opt (parser, in_statement_expr);
  /* APPLE LOCAL begin radar 5982990 */
  if (objc_sjlj_exceptions)
    objc_mark_locals_volatile (NULL);
  /* APPLE LOCAL end radar 5982990 */
  /* Finish the compound-statement.  */
  finish_compound_stmt (compound_stmt);
  /* Consume the `}'.  */
  cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");

  return compound_stmt;
}