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
struct c_type_name {int dummy; } ;
struct c_expr {int /*<<< orphan*/  original_code; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 scalar_t__ C_TYPE_VARIABLE_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_MARK ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_compound_literal (scalar_t__,int /*<<< orphan*/ ) ; 
 struct c_expr c_parser_braced_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct c_expr c_parser_postfix_expression_after_primary (int /*<<< orphan*/ *,struct c_expr) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_init () ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 scalar_t__ groktypename (struct c_type_name*) ; 
 int /*<<< orphan*/  maybe_warn_string_init (scalar_t__,struct c_expr) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  start_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct c_expr
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      struct c_type_name *type_name)
{
  tree type;
  struct c_expr init;
  struct c_expr expr;
  start_init (NULL_TREE, NULL, 0);
  type = groktypename (type_name);
  if (type != error_mark_node && C_TYPE_VARIABLE_SIZE (type))
    {
      error ("compound literal has variable size");
      type = error_mark_node;
    }
  init = c_parser_braced_init (parser, type, false);
  finish_init ();
  maybe_warn_string_init (type, init);

  if (pedantic && !flag_isoc99)
    pedwarn ("ISO C90 forbids compound literals");
  expr.value = build_compound_literal (type, init.value);
  expr.original_code = ERROR_MARK;
  return c_parser_postfix_expression_after_primary (parser, expr);
}