#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_12__ {char* type_definition_forbidden_message; int in_type_id_in_expr_p; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wold_style_cast ; 
 int /*<<< orphan*/  VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_c_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cast_valid_in_integral_constant_expression_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_rollback_tokens (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_save_tokens (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_error_occurred (TYPE_1__*) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_1__*,char*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_1__*) ; 
 scalar_t__ cp_parser_skip_to_closing_parenthesis (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_type_id (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_unary_expression (TYPE_1__*,int,int) ; 
 scalar_t__ current_lang_name ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  in_system_header ; 
 scalar_t__ lang_name_c ; 
 scalar_t__ warn_old_style_cast ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static tree
cp_parser_cast_expression (cp_parser *parser, bool address_p, bool cast_p)
{
  /* If it's a `(', then we might be looking at a cast.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_PAREN))
    {
      tree type = NULL_TREE;
      tree expr = NULL_TREE;
      bool compound_literal_p;
      const char *saved_message;

      /* There's no way to know yet whether or not this is a cast.
	 For example, `(int (3))' is a unary-expression, while `(int)
	 3' is a cast.  So, we resort to parsing tentatively.  */
      cp_parser_parse_tentatively (parser);
      /* Types may not be defined in a cast.  */
      saved_message = parser->type_definition_forbidden_message;
      parser->type_definition_forbidden_message
	= "types may not be defined in casts";
      /* Consume the `('.  */
      cp_lexer_consume_token (parser->lexer);
      /* A very tricky bit is that `(struct S) { 3 }' is a
	 compound-literal (which we permit in C++ as an extension).
	 But, that construct is not a cast-expression -- it is a
	 postfix-expression.  (The reason is that `(struct S) { 3 }.i'
	 is legal; if the compound-literal were a cast-expression,
	 you'd need an extra set of parentheses.)  But, if we parse
	 the type-id, and it happens to be a class-specifier, then we
	 will commit to the parse at that point, because we cannot
	 undo the action that is done when creating a new class.  So,
	 then we cannot back up and do a postfix-expression.

	 Therefore, we scan ahead to the closing `)', and check to see
	 if the token after the `)' is a `{'.  If so, we are not
	 looking at a cast-expression.

	 Save tokens so that we can put them back.  */
      cp_lexer_save_tokens (parser->lexer);
      /* Skip tokens until the next token is a closing parenthesis.
	 If we find the closing `)', and the next token is a `{', then
	 we are looking at a compound-literal.  */
      compound_literal_p
	= (cp_parser_skip_to_closing_parenthesis (parser, false, false,
						  /*consume_paren=*/true)
	   && cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE));
      /* Roll back the tokens we skipped.  */
      cp_lexer_rollback_tokens (parser->lexer);
      /* If we were looking at a compound-literal, simulate an error
	 so that the call to cp_parser_parse_definitely below will
	 fail.  */
      if (compound_literal_p)
	cp_parser_simulate_error (parser);
      else
	{
	  bool saved_in_type_id_in_expr_p = parser->in_type_id_in_expr_p;
	  parser->in_type_id_in_expr_p = true;
	  /* Look for the type-id.  */
	  type = cp_parser_type_id (parser);
	  /* Look for the closing `)'.  */
	  cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'");
	  parser->in_type_id_in_expr_p = saved_in_type_id_in_expr_p;
	}

      /* Restore the saved message.  */
      parser->type_definition_forbidden_message = saved_message;

      /* If ok so far, parse the dependent expression. We cannot be
	 sure it is a cast. Consider `(T ())'.  It is a parenthesized
	 ctor of T, but looks like a cast to function returning T
	 without a dependent expression.  */
      if (!cp_parser_error_occurred (parser))
	expr = cp_parser_cast_expression (parser,
					  /*address_p=*/false,
					  /*cast_p=*/true);

      if (cp_parser_parse_definitely (parser))
	{
	  /* Warn about old-style casts, if so requested.  */
	  if (warn_old_style_cast
	      && !in_system_header
	      && !VOID_TYPE_P (type)
	      && current_lang_name != lang_name_c)
	    warning (OPT_Wold_style_cast, "use of old-style cast");

	  /* Only type conversions to integral or enumeration types
	     can be used in constant-expressions.  */
	  if (!cast_valid_in_integral_constant_expression_p (type)
	      && (cp_parser_non_integral_constant_expression
		  (parser,
		   "a cast to a type other than an integral or "
		   "enumeration type")))
	    return error_mark_node;

	  /* Perform the cast.  */
	  expr = build_c_cast (type, expr);
	  return expr;
	}
    }

  /* If we get here, then it's not a cast, so it must be a
     unary-expression.  */
  return cp_parser_unary_expression (parser, address_p, cast_p);
}