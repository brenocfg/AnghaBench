#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_24__ {int /*<<< orphan*/  value; } ;
struct TYPE_25__ {int type; TYPE_1__ u; int /*<<< orphan*/  keyword; } ;
typedef  TYPE_2__ cp_token ;
struct TYPE_26__ {int greater_than_is_operator_p; int /*<<< orphan*/  non_integral_constant_expression_p; int /*<<< orphan*/  allow_non_integral_constant_expression_p; int /*<<< orphan*/  integral_constant_expression_p; int /*<<< orphan*/  scope; int /*<<< orphan*/  local_variables_forbidden_p; int /*<<< orphan*/  lexer; int /*<<< orphan*/  in_function_body; int /*<<< orphan*/  translate_strings_p; } ;
typedef  TYPE_3__ cp_parser ;
typedef  int /*<<< orphan*/  cp_id_kind ;

/* Variables and functions */
#define  CPP_CHAR 152 
 int const CPP_CLOSE_BRACE ; 
 int const CPP_CLOSE_PAREN ; 
 int const CPP_CLOSE_SQUARE ; 
 int const CPP_COMMA ; 
 int const CPP_DEREF ; 
 int const CPP_DOT ; 
 int const CPP_GREATER ; 
#define  CPP_KEYWORD 151 
 int const CPP_MINUS_MINUS ; 
#define  CPP_NAME 150 
#define  CPP_NESTED_NAME_SPECIFIER 149 
#define  CPP_NUMBER 148 
 int const CPP_OBJC_STRING ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
#define  CPP_OPEN_PAREN 147 
 int const CPP_OPEN_SQUARE ; 
 int const CPP_PLUS_PLUS ; 
#define  CPP_SCOPE 146 
 int const CPP_SEMICOLON ; 
#define  CPP_STRING 145 
#define  CPP_TEMPLATE_ID 144 
#define  CPP_WCHAR 143 
#define  CPP_WSTRING 142 
#define  CPP_XOR 141 
 int /*<<< orphan*/  CP_ID_KIND_NONE ; 
 int /*<<< orphan*/  REAL_CST ; 
#define  RID_AT_ENCODE 140 
#define  RID_AT_PROTOCOL 139 
#define  RID_AT_SELECTOR 138 
#define  RID_C99_FUNCTION_NAME 137 
#define  RID_FALSE 136 
#define  RID_FUNCTION_NAME 135 
#define  RID_NULL 134 
#define  RID_OFFSETOF 133 
#define  RID_OPERATOR 132 
#define  RID_PRETTY_FUNCTION_NAME 131 
#define  RID_THIS 130 
#define  RID_TRUE 129 
#define  RID_VA_ARG 128 
 int /*<<< orphan*/  SCOPE_REF ; 
 int /*<<< orphan*/  TEMPLATE_ID_EXPR ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DECL ; 
 int /*<<< orphan*/  begin_stmt_expr () ; 
 int /*<<< orphan*/  boolean_false_node ; 
 int /*<<< orphan*/  boolean_true_node ; 
 int /*<<< orphan*/  build_x_va_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_dialect_objc () ; 
 int /*<<< orphan*/  check_for_out_of_scope_variable (int /*<<< orphan*/ ) ; 
 TYPE_2__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_objc_property_reference_prefix (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_allow_gnu_extensions_p (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_assignment_expression (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_parser_block_literal_expr (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_builtin_offsetof (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_compound_statement (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  cp_parser_expression (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_parser_id_expression (TYPE_3__*,int,int,int*,int,int) ; 
 int /*<<< orphan*/  cp_parser_lookup_name (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_non_integral_constant_expression (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  cp_parser_objc_expression (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_objc_reference_expression (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_3__*,int const,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_statement (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_string_literal (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_type_id (TYPE_3__*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_fname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_id_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,char const**) ; 
 int /*<<< orphan*/  finish_parenthesized_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_stmt_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  finish_this_expr () ; 
 int /*<<< orphan*/  flag_blocks ; 
 int /*<<< orphan*/  local_variable_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  none_type ; 
 int /*<<< orphan*/  null_node ; 
 int /*<<< orphan*/  objc_lookup_ivar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 

__attribute__((used)) static tree
cp_parser_primary_expression (cp_parser *parser,
			      bool address_p,
			      bool cast_p,
			      bool template_arg_p,
			      cp_id_kind *idk)
{
  cp_token *token;

  /* Assume the primary expression is not an id-expression.  */
  *idk = CP_ID_KIND_NONE;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  switch (token->type)
    {
      /* APPLE LOCAL begin blocks 6040305 (cf) */
    case CPP_XOR:
      if (flag_blocks)
	{
	  tree expr = cp_parser_block_literal_expr (parser);
	  return expr;
	}
      cp_parser_error (parser, "expected primary-expression");
      return error_mark_node;
      /* APPLE LOCAL end blocks 6040305 (cf) */
      /* literal:
	   integer-literal
	   character-literal
	   floating-literal
	   string-literal
	   boolean-literal  */
    case CPP_CHAR:
    case CPP_WCHAR:
    case CPP_NUMBER:
      token = cp_lexer_consume_token (parser->lexer);
      /* Floating-point literals are only allowed in an integral
	 constant expression if they are cast to an integral or
	 enumeration type.  */
      if (TREE_CODE (token->u.value) == REAL_CST
	  && parser->integral_constant_expression_p
	  && pedantic)
	{
	  /* CAST_P will be set even in invalid code like "int(2.7 +
	     ...)".   Therefore, we have to check that the next token
	     is sure to end the cast.  */
	  if (cast_p)
	    {
	      cp_token *next_token;

	      next_token = cp_lexer_peek_token (parser->lexer);
	      if (/* The comma at the end of an
		     enumerator-definition.  */
		  next_token->type != CPP_COMMA
		  /* The curly brace at the end of an enum-specifier.  */
		  && next_token->type != CPP_CLOSE_BRACE
		  /* The end of a statement.  */
		  && next_token->type != CPP_SEMICOLON
		  /* The end of the cast-expression.  */
		  && next_token->type != CPP_CLOSE_PAREN
		  /* The end of an array bound.  */
		  && next_token->type != CPP_CLOSE_SQUARE
		  /* The closing ">" in a template-argument-list.  */
		  && (next_token->type != CPP_GREATER
		      || parser->greater_than_is_operator_p))
		cast_p = false;
	    }

	  /* If we are within a cast, then the constraint that the
	     cast is to an integral or enumeration type will be
	     checked at that point.  If we are not within a cast, then
	     this code is invalid.  */
	  if (!cast_p)
	    cp_parser_non_integral_constant_expression
	      (parser, "floating-point literal");
	}
      return token->u.value;

    case CPP_STRING:
    case CPP_WSTRING:
      /* ??? Should wide strings be allowed when parser->translate_strings_p
	 is false (i.e. in attributes)?  If not, we can kill the third
	 argument to cp_parser_string_literal.  */
      return cp_parser_string_literal (parser,
				       parser->translate_strings_p,
				       true);

    case CPP_OPEN_PAREN:
      {
	tree expr;
	bool saved_greater_than_is_operator_p;

	/* Consume the `('.  */
	cp_lexer_consume_token (parser->lexer);
	/* Within a parenthesized expression, a `>' token is always
	   the greater-than operator.  */
	saved_greater_than_is_operator_p
	  = parser->greater_than_is_operator_p;
	parser->greater_than_is_operator_p = true;
	/* If we see `( { ' then we are looking at the beginning of
	   a GNU statement-expression.  */
	if (cp_parser_allow_gnu_extensions_p (parser)
	    && cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
	  {
	    /* Statement-expressions are not allowed by the standard.  */
	    if (pedantic)
	      pedwarn ("ISO C++ forbids braced-groups within expressions");

	    /* And they're not allowed outside of a function-body; you
	       cannot, for example, write:

		 int i = ({ int j = 3; j + 1; });

	       at class or namespace scope.  */
	    if (!parser->in_function_body)
	      error ("statement-expressions are allowed only inside functions");
	    /* Start the statement-expression.  */
	    expr = begin_stmt_expr ();
	    /* Parse the compound-statement.  */
	    /* APPLE LOCAL radar 5982990 */
	    cp_parser_compound_statement (parser, expr, false, false);
	    /* Finish up.  */
	    expr = finish_stmt_expr (expr, false);
	  }
	else
	  {
	    /* Parse the parenthesized expression.  */
	    expr = cp_parser_expression (parser, cast_p);
	    /* Let the front end know that this expression was
	       enclosed in parentheses. This matters in case, for
	       example, the expression is of the form `A::B', since
	       `&A::B' might be a pointer-to-member, but `&(A::B)' is
	       not.  */
	    finish_parenthesized_expr (expr);
	  }
	/* The `>' token might be the end of a template-id or
	   template-parameter-list now.  */
	parser->greater_than_is_operator_p
	  = saved_greater_than_is_operator_p;
	/* Consume the `)'.  */
	if (!cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'"))
	  cp_parser_skip_to_end_of_statement (parser);

	return expr;
      }

    case CPP_KEYWORD:
      switch (token->keyword)
	{
	  /* These two are the boolean literals.  */
	case RID_TRUE:
	  cp_lexer_consume_token (parser->lexer);
	  return boolean_true_node;
	case RID_FALSE:
	  cp_lexer_consume_token (parser->lexer);
	  return boolean_false_node;

	  /* The `__null' literal.  */
	case RID_NULL:
	  cp_lexer_consume_token (parser->lexer);
	  return null_node;

	  /* Recognize the `this' keyword.  */
	case RID_THIS:
	  cp_lexer_consume_token (parser->lexer);
	  if (parser->local_variables_forbidden_p)
	    {
	      error ("%<this%> may not be used in this context");
	      return error_mark_node;
	    }
	  /* Pointers cannot appear in constant-expressions.  */
	  if (cp_parser_non_integral_constant_expression (parser,
							  "`this'"))
	    return error_mark_node;
	  return finish_this_expr ();

	  /* The `operator' keyword can be the beginning of an
	     id-expression.  */
	case RID_OPERATOR:
	  goto id_expression;

	case RID_FUNCTION_NAME:
	case RID_PRETTY_FUNCTION_NAME:
	case RID_C99_FUNCTION_NAME:
	  /* The symbols __FUNCTION__, __PRETTY_FUNCTION__, and
	     __func__ are the names of variables -- but they are
	     treated specially.  Therefore, they are handled here,
	     rather than relying on the generic id-expression logic
	     below.  Grammatically, these names are id-expressions.

	     Consume the token.  */
	  token = cp_lexer_consume_token (parser->lexer);
	  /* Look up the name.  */
	  return finish_fname (token->u.value);

	case RID_VA_ARG:
	  {
	    tree expression;
	    tree type;

	    /* The `__builtin_va_arg' construct is used to handle
	       `va_arg'.  Consume the `__builtin_va_arg' token.  */
	    cp_lexer_consume_token (parser->lexer);
	    /* Look for the opening `('.  */
	    cp_parser_require (parser, CPP_OPEN_PAREN, "`('");
	    /* Now, parse the assignment-expression.  */
	    expression = cp_parser_assignment_expression (parser,
							  /*cast_p=*/false);
	    /* Look for the `,'.  */
	    cp_parser_require (parser, CPP_COMMA, "`,'");
	    /* Parse the type-id.  */
	    type = cp_parser_type_id (parser);
	    /* Look for the closing `)'.  */
	    cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");
	    /* Using `va_arg' in a constant-expression is not
	       allowed.  */
	    if (cp_parser_non_integral_constant_expression (parser,
							    "`va_arg'"))
	      return error_mark_node;
	    return build_x_va_arg (expression, type);
	  }

	case RID_OFFSETOF:
	  return cp_parser_builtin_offsetof (parser);

	  /* Objective-C++ expressions.  */
	case RID_AT_ENCODE:
	case RID_AT_PROTOCOL:
	case RID_AT_SELECTOR:
	  return cp_parser_objc_expression (parser);

	default:
	  cp_parser_error (parser, "expected primary-expression");
	  return error_mark_node;
	}

      /* An id-expression can start with either an identifier, a
	 `::' as the beginning of a qualified-id, or the "operator"
	 keyword.  */
    case CPP_NAME:
    case CPP_SCOPE:
    case CPP_TEMPLATE_ID:
    case CPP_NESTED_NAME_SPECIFIER:
      {
	tree id_expression;
	tree decl;
	const char *error_msg;
	bool template_p;
	bool done;

      id_expression:
	/* Parse the id-expression.  */
	id_expression
	  = cp_parser_id_expression (parser,
				     /*template_keyword_p=*/false,
				     /*check_dependency_p=*/true,
				     &template_p,
				     /*declarator_p=*/false,
				     /*optional_p=*/false);
	if (id_expression == error_mark_node)
	  return error_mark_node;
	token = cp_lexer_peek_token (parser->lexer);
	done = (token->type != CPP_OPEN_SQUARE
		&& token->type != CPP_OPEN_PAREN
		&& token->type != CPP_DOT
		&& token->type != CPP_DEREF
		&& token->type != CPP_PLUS_PLUS
		&& token->type != CPP_MINUS_MINUS);
	/* If we have a template-id, then no further lookup is
	   required.  If the template-id was for a template-class, we
	   will sometimes have a TYPE_DECL at this point.  */
	if (TREE_CODE (id_expression) == TEMPLATE_ID_EXPR
		 || TREE_CODE (id_expression) == TYPE_DECL)
	  decl = id_expression;
	/* Look up the name.  */
	else
	  {
	    tree ambiguous_decls;

	    decl = cp_parser_lookup_name (parser, id_expression,
					  none_type,
					  template_p,
					  /*is_namespace=*/false,
					  /*check_dependency=*/true,
					  &ambiguous_decls);
	    /* If the lookup was ambiguous, an error will already have
	       been issued.  */
	    if (ambiguous_decls)
	      return error_mark_node;

	    /* APPLE LOCAL begin radar 5277239 */
	    if (TREE_CODE (decl) == TYPE_DECL 
		&& cp_objc_property_reference_prefix (parser, TREE_TYPE (decl)))
	      return cp_parser_objc_reference_expression (parser, decl);
	    /* APPLE LOCAL end radar 5277239 */
	    /* In Objective-C++, an instance variable (ivar) may be preferred
	       to whatever cp_parser_lookup_name() found.  */
	    decl = objc_lookup_ivar (decl, id_expression);

	    /* If name lookup gives us a SCOPE_REF, then the
	       qualifying scope was dependent.  */
	    if (TREE_CODE (decl) == SCOPE_REF)
	      {
		/* At this point, we do not know if DECL is a valid
		   integral constant expression.  We assume that it is
		   in fact such an expression, so that code like:

		      template <int N> struct A {
			int a[B<N>::i];
		      };
		     
		   is accepted.  At template-instantiation time, we
		   will check that B<N>::i is actually a constant.  */
		return decl;
	      }
	    /* Check to see if DECL is a local variable in a context
	       where that is forbidden.  */
	    if (parser->local_variables_forbidden_p
		&& local_variable_p (decl))
	      {
		/* It might be that we only found DECL because we are
		   trying to be generous with pre-ISO scoping rules.
		   For example, consider:

		     int i;
		     void g() {
		       for (int i = 0; i < 10; ++i) {}
		       extern void f(int j = i);
		     }

		   Here, name look up will originally find the out
		   of scope `i'.  We need to issue a warning message,
		   but then use the global `i'.  */
		decl = check_for_out_of_scope_variable (decl);
		if (local_variable_p (decl))
		  {
		    error ("local variable %qD may not appear in this context",
			   decl);
		    return error_mark_node;
		  }
	      }
	  }

	decl = (finish_id_expression
		(id_expression, decl, parser->scope,
		 idk,
		 parser->integral_constant_expression_p,
		 parser->allow_non_integral_constant_expression_p,
		 &parser->non_integral_constant_expression_p,
		 template_p, done, address_p,
		 template_arg_p,
		 &error_msg));
	if (error_msg)
	  cp_parser_error (parser, error_msg);
	return decl;
      }

      /* Anything else is an error.  */
    default:
      /* ...unless we have an Objective-C++ message or string literal, that is.  */
      if (c_dialect_objc ()
	  && (token->type == CPP_OPEN_SQUARE || token->type == CPP_OBJC_STRING))
	return cp_parser_objc_expression (parser);

      cp_parser_error (parser, "expected primary-expression");
      return error_mark_node;
    }
}