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
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 scalar_t__ cp_parser_parenthesized_expression_list (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ void_zero_node ; 

__attribute__((used)) static tree
cp_parser_new_initializer (cp_parser* parser)
{
  tree expression_list;

  expression_list = (cp_parser_parenthesized_expression_list
		     (parser, false, /*cast_p=*/false,
		      /*non_constant_p=*/NULL));
  if (!expression_list)
    expression_list = void_zero_node;

  return expression_list;
}