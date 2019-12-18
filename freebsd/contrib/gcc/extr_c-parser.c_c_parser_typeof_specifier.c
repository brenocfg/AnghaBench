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
struct c_typespec {int /*<<< orphan*/  spec; int /*<<< orphan*/  kind; } ;
struct c_type_name {int dummy; } ;
struct c_expr {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ CONSTANT_CLASS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ DECL_C_BIT_FIELD (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_TYPEOF ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 struct c_expr c_parser_expression (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_starts_typename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct c_type_name* c_parser_type_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctsk_typeof ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  groktypename (struct c_type_name*) ; 
 int /*<<< orphan*/  in_typeof ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  pop_maybe_used (int) ; 
 int /*<<< orphan*/  skip_evaluation ; 
 int variably_modified_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static struct c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  struct c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_node;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF));
  c_parser_consume_token (parser);
  skip_evaluation++;
  in_typeof++;
  if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      skip_evaluation--;
      in_typeof--;
      return ret;
    }
  if (c_parser_next_token_starts_typename (parser))
    {
      struct c_type_name *type = c_parser_type_name (parser);
      skip_evaluation--;
      in_typeof--;
      if (type != NULL)
	{
	  ret.spec = groktypename (type);
	  pop_maybe_used (variably_modified_type_p (ret.spec, NULL_TREE));
	}
    }
  else
    {
      bool was_vm;
      struct c_expr expr = c_parser_expression (parser);
      skip_evaluation--;
      in_typeof--;
      if (TREE_CODE (expr.value) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (TREE_OPERAND (expr.value, 1)))
	error ("%<typeof%> applied to a bit-field");
      ret.spec = TREE_TYPE (expr.value);
      was_vm = variably_modified_type_p (ret.spec, NULL_TREE);
      /* This should be returned with the type so that when the type
	 is evaluated, this can be evaluated.  For now, we avoid
	 evaluation when the context might.  */
      if (!skip_evaluation && was_vm)
	{
	  tree e = expr.value;

	  /* If the expression is not of a type to which we cannot assign a line
	     number, wrap the thing in a no-op NOP_EXPR.  */
	  if (DECL_P (e) || CONSTANT_CLASS_P (e))
	    e = build1 (NOP_EXPR, void_type_node, e);

	  if (EXPR_P (e))
	    SET_EXPR_LOCATION (e, input_location);

	  add_stmt (e);
	}
      pop_maybe_used (was_vm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
  return ret;
}