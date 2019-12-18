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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  c_begin_compound_stmt (int) ; 
 int /*<<< orphan*/  c_end_compound_stmt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c_parser_compound_statement_nostart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 scalar_t__ flag_objc_sjlj_exceptions ; 
 int /*<<< orphan*/  objc_mark_locals_volatile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
c_parser_objc_synch_compound_statement (c_parser *parser)
{
  tree stmt;
  if (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    return error_mark_node;
  stmt = c_begin_compound_stmt (true);
  c_parser_compound_statement_nostart (parser);
  if (flag_objc_sjlj_exceptions)
    objc_mark_locals_volatile (NULL);
  return c_end_compound_stmt (stmt, true);
}