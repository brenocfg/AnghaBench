#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_19__ {scalar_t__ type; int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_20__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_18__ {int keyword; } ;

/* Variables and functions */
#define  ADDR_EXPR 142 
 int ALIGNOF_EXPR ; 
#define  BIT_NOT_EXPR 141 
 scalar_t__ CPP_AND_AND ; 
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_MINUS_MINUS ; 
 scalar_t__ CPP_PLUS_PLUS ; 
 int /*<<< orphan*/  CPP_SCOPE ; 
 int ERROR_MARK ; 
 int IMAGPART_EXPR ; 
#define  INDIRECT_REF 140 
#define  NEGATE_EXPR 139 
#define  PREDECREMENT_EXPR 138 
#define  PREINCREMENT_EXPR 137 
 int REALPART_EXPR ; 
#define  RID_ALIGNOF 136 
#define  RID_DELETE 135 
#define  RID_EXTENSION 134 
#define  RID_IMAGPART 133 
#define  RID_NEW 132 
#define  RID_REALPART 131 
#define  RID_SIZEOF 130 
 int SIZEOF_EXPR ; 
#define  TRUTH_NOT_EXPR 129 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
#define  UNARY_PLUS_EXPR 128 
 int /*<<< orphan*/  build_x_indirect_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  build_x_unary_op (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_16__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_cast_expression (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  cp_parser_delete_expression (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_extension_opt (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  cp_parser_identifier (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_new_expression (TYPE_2__*) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cp_parser_postfix_expression (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  cp_parser_simple_cast_expression (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_sizeof_operand (TYPE_2__*,int) ; 
 int cp_parser_unary_operator (TYPE_1__*) ; 
 int /*<<< orphan*/  cxx_sizeof_or_alignof_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxx_sizeof_or_alignof_type (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_label_address_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_unary_op_expr (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int pedantic ; 

__attribute__((used)) static tree
cp_parser_unary_expression (cp_parser *parser, bool address_p, bool cast_p)
{
  cp_token *token;
  enum tree_code unary_operator;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  /* Some keywords give away the kind of expression.  */
  if (token->type == CPP_KEYWORD)
    {
      enum rid keyword = token->keyword;

      switch (keyword)
	{
	case RID_ALIGNOF:
	case RID_SIZEOF:
	  {
	    tree operand;
	    enum tree_code op;

	    op = keyword == RID_ALIGNOF ? ALIGNOF_EXPR : SIZEOF_EXPR;
	    /* Consume the token.  */
	    cp_lexer_consume_token (parser->lexer);
	    /* Parse the operand.  */
	    operand = cp_parser_sizeof_operand (parser, keyword);

	    if (TYPE_P (operand))
	      return cxx_sizeof_or_alignof_type (operand, op, true);
	    else
	      return cxx_sizeof_or_alignof_expr (operand, op);
	  }

	case RID_NEW:
	  return cp_parser_new_expression (parser);

	case RID_DELETE:
	  return cp_parser_delete_expression (parser);

	case RID_EXTENSION:
	  {
	    /* The saved value of the PEDANTIC flag.  */
	    int saved_pedantic;
	    tree expr;

	    /* Save away the PEDANTIC flag.  */
	    cp_parser_extension_opt (parser, &saved_pedantic);
	    /* Parse the cast-expression.  */
	    expr = cp_parser_simple_cast_expression (parser);
	    /* Restore the PEDANTIC flag.  */
	    pedantic = saved_pedantic;

	    return expr;
	  }

	case RID_REALPART:
	case RID_IMAGPART:
	  {
	    tree expression;

	    /* Consume the `__real__' or `__imag__' token.  */
	    cp_lexer_consume_token (parser->lexer);
	    /* Parse the cast-expression.  */
	    expression = cp_parser_simple_cast_expression (parser);
	    /* Create the complete representation.  */
	    return build_x_unary_op ((keyword == RID_REALPART
				      ? REALPART_EXPR : IMAGPART_EXPR),
				     expression);
	  }
	  break;

	default:
	  break;
	}
    }

  /* Look for the `:: new' and `:: delete', which also signal the
     beginning of a new-expression, or delete-expression,
     respectively.  If the next token is `::', then it might be one of
     these.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_SCOPE))
    {
      enum rid keyword;

      /* See if the token after the `::' is one of the keywords in
	 which we're interested.  */
      keyword = cp_lexer_peek_nth_token (parser->lexer, 2)->keyword;
      /* If it's `new', we have a new-expression.  */
      if (keyword == RID_NEW)
	return cp_parser_new_expression (parser);
      /* Similarly, for `delete'.  */
      else if (keyword == RID_DELETE)
	return cp_parser_delete_expression (parser);
    }

  /* Look for a unary operator.  */
  unary_operator = cp_parser_unary_operator (token);
  /* The `++' and `--' operators can be handled similarly, even though
     they are not technically unary-operators in the grammar.  */
  if (unary_operator == ERROR_MARK)
    {
      if (token->type == CPP_PLUS_PLUS)
	unary_operator = PREINCREMENT_EXPR;
      else if (token->type == CPP_MINUS_MINUS)
	unary_operator = PREDECREMENT_EXPR;
      /* Handle the GNU address-of-label extension.  */
      else if (cp_parser_allow_gnu_extensions_p (parser)
	       && token->type == CPP_AND_AND)
	{
	  tree identifier;

	  /* Consume the '&&' token.  */
	  cp_lexer_consume_token (parser->lexer);
	  /* Look for the identifier.  */
	  identifier = cp_parser_identifier (parser);
	  /* Create an expression representing the address.  */
	  return finish_label_address_expr (identifier);
	}
    }
  if (unary_operator != ERROR_MARK)
    {
      tree cast_expression;
      tree expression = error_mark_node;
      const char *non_constant_p = NULL;

      /* Consume the operator token.  */
      token = cp_lexer_consume_token (parser->lexer);
      /* Parse the cast-expression.  */
      cast_expression
	= cp_parser_cast_expression (parser,
				     unary_operator == ADDR_EXPR,
				     /*cast_p=*/false);
      /* Now, build an appropriate representation.  */
      switch (unary_operator)
	{
	case INDIRECT_REF:
	  non_constant_p = "`*'";
	  expression = build_x_indirect_ref (cast_expression, "unary *");
	  break;

	case ADDR_EXPR:
	  non_constant_p = "`&'";
	  /* Fall through.  */
	case BIT_NOT_EXPR:
	  expression = build_x_unary_op (unary_operator, cast_expression);
	  break;

	case PREINCREMENT_EXPR:
	case PREDECREMENT_EXPR:
	  non_constant_p = (unary_operator == PREINCREMENT_EXPR
			    ? "`++'" : "`--'");
	  /* Fall through.  */
	case UNARY_PLUS_EXPR:
	case NEGATE_EXPR:
	case TRUTH_NOT_EXPR:
	  expression = finish_unary_op_expr (unary_operator, cast_expression);
	  break;

	default:
	  gcc_unreachable ();
	}

      if (non_constant_p
	  && cp_parser_non_integral_constant_expression (parser,
							 non_constant_p))
	expression = error_mark_node;

      return expression;
    }

  return cp_parser_postfix_expression (parser, address_p, cast_p);
}