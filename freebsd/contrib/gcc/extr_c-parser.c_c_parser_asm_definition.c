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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ c_parser_simple_asm_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cgraph_add_asm_node (scalar_t__) ; 

__attribute__((used)) static void
c_parser_asm_definition (c_parser *parser)
{
  tree asm_str = c_parser_simple_asm_expr (parser);
  if (asm_str)
    cgraph_add_asm_node (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}