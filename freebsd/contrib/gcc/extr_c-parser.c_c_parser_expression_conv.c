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
struct c_expr {int dummy; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 struct c_expr c_parser_expression (int /*<<< orphan*/ *) ; 
 struct c_expr default_function_array_conversion (struct c_expr) ; 

__attribute__((used)) static struct c_expr
c_parser_expression_conv (c_parser *parser)
{
  struct c_expr expr;
  expr = c_parser_expression (parser);
  expr = default_function_array_conversion (expr);
  return expr;
}