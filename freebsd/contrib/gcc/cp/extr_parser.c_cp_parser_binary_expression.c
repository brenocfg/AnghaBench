#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum cp_parser_prec { ____Placeholder_cp_parser_prec } cp_parser_prec ;
struct TYPE_13__ {size_t type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_14__ {int prec; int tree_type; int lhs_type; int /*<<< orphan*/  lhs; } ;
typedef  TYPE_2__ cp_parser_expression_stack_entry ;
typedef  TYPE_2__* cp_parser_expression_stack ;
struct TYPE_15__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_4__ cp_parser ;
struct TYPE_12__ {int tree_type; } ;

/* Variables and functions */
 int ERROR_MARK ; 
 int PREC_NOT_OPERATOR ; 
 int TOKEN_PRECEDENCE (TYPE_1__*) ; 
 TYPE_10__* binops_by_token ; 
 int /*<<< orphan*/  build_x_binary_op (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_cast_expression (TYPE_4__*,int,int) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  cp_parser_simple_cast_expression (TYPE_4__*) ; 
 int /*<<< orphan*/  error_mark_node ; 

__attribute__((used)) static tree
cp_parser_binary_expression (cp_parser* parser, bool cast_p)
{
  cp_parser_expression_stack stack;
  cp_parser_expression_stack_entry *sp = &stack[0];
  tree lhs, rhs;
  cp_token *token;
  enum tree_code tree_type, lhs_type, rhs_type;
  enum cp_parser_prec prec = PREC_NOT_OPERATOR, new_prec, lookahead_prec;
  bool overloaded_p;

  /* Parse the first expression.  */
  lhs = cp_parser_cast_expression (parser, /*address_p=*/false, cast_p);
  lhs_type = ERROR_MARK;

  for (;;)
    {
      /* Get an operator token.  */
      token = cp_lexer_peek_token (parser->lexer);

      new_prec = TOKEN_PRECEDENCE (token);

      /* Popping an entry off the stack means we completed a subexpression:
	 - either we found a token which is not an operator (`>' where it is not
	   an operator, or prec == PREC_NOT_OPERATOR), in which case popping
	   will happen repeatedly;
	 - or, we found an operator which has lower priority.  This is the case
	   where the recursive descent *ascends*, as in `3 * 4 + 5' after
	   parsing `3 * 4'.  */
      if (new_prec <= prec)
	{
	  if (sp == stack)
	    break;
	  else
	    goto pop;
	}

     get_rhs:
      tree_type = binops_by_token[token->type].tree_type;

      /* We used the operator token.  */
      cp_lexer_consume_token (parser->lexer);

      /* Extract another operand.  It may be the RHS of this expression
	 or the LHS of a new, higher priority expression.  */
      rhs = cp_parser_simple_cast_expression (parser);
      rhs_type = ERROR_MARK;

      /* Get another operator token.  Look up its precedence to avoid
	 building a useless (immediately popped) stack entry for common
	 cases such as 3 + 4 + 5 or 3 * 4 + 5.  */
      token = cp_lexer_peek_token (parser->lexer);
      lookahead_prec = TOKEN_PRECEDENCE (token);
      if (lookahead_prec > new_prec)
	{
	  /* ... and prepare to parse the RHS of the new, higher priority
	     expression.  Since precedence levels on the stack are
	     monotonically increasing, we do not have to care about
	     stack overflows.  */
	  sp->prec = prec;
	  sp->tree_type = tree_type;
	  sp->lhs = lhs;
	  sp->lhs_type = lhs_type;
	  sp++;
	  lhs = rhs;
	  lhs_type = rhs_type;
	  prec = new_prec;
	  new_prec = lookahead_prec;
	  goto get_rhs;

	 pop:
	  /* If the stack is not empty, we have parsed into LHS the right side
	     (`4' in the example above) of an expression we had suspended.
	     We can use the information on the stack to recover the LHS (`3')
	     from the stack together with the tree code (`MULT_EXPR'), and
	     the precedence of the higher level subexpression
	     (`PREC_ADDITIVE_EXPRESSION').  TOKEN is the CPP_PLUS token,
	     which will be used to actually build the additive expression.  */
	  --sp;
	  prec = sp->prec;
	  tree_type = sp->tree_type;
	  rhs = lhs;
	  rhs_type = lhs_type;
	  lhs = sp->lhs;
	  lhs_type = sp->lhs_type;
	}

      overloaded_p = false;
      lhs = build_x_binary_op (tree_type, lhs, lhs_type, rhs, rhs_type,
			       &overloaded_p);
      lhs_type = tree_type;

      /* If the binary operator required the use of an overloaded operator,
	 then this expression cannot be an integral constant-expression.
	 An overloaded operator can be used even if both operands are
	 otherwise permissible in an integral constant-expression if at
	 least one of the operands is of enumeration type.  */

      if (overloaded_p
	  && (cp_parser_non_integral_constant_expression
	      (parser, "calls to overloaded operators")))
	return error_mark_node;
    }

  return lhs;
}