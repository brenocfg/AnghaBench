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
 int /*<<< orphan*/  c_parser_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_stmt_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_stmt_list () ; 

__attribute__((used)) static tree
c_parser_omp_structured_block (c_parser *parser)
{
  tree stmt = push_stmt_list ();
  c_parser_statement (parser);
  return pop_stmt_list (stmt);
}