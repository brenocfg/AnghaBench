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
 int /*<<< orphan*/  c_begin_compound_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_end_compound_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flag_isoc99 ; 

__attribute__((used)) static tree
c_parser_c99_block_statement (c_parser *parser)
{
  tree block = c_begin_compound_stmt (flag_isoc99);
  c_parser_statement (parser);
  return c_end_compound_stmt (block, flag_isoc99);
}