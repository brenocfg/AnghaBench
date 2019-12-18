#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  location_t ;
struct TYPE_20__ {int /*<<< orphan*/  in_statement; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_decl_specifier_seq ;
struct TYPE_19__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_EQ ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_NAMED ; 
 int /*<<< orphan*/  IN_OMP_FOR ; 
 int /*<<< orphan*/  LOOKUP_ONLYCONVERTING ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_FOR ; 
 int /*<<< orphan*/  cp_finish_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_18__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_abort_tentative_parse (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_parser_asm_specification_opt (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_parser_assignment_expression (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * cp_parser_attributes_opt (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_parser_condition (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_parser_declarator (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_error_occurred (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_parser_expression (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_closing_parenthesis (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_statement (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_type_specifier_seq (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * finish_omp_for (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_scope (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pop_stmt_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * push_stmt_list () ; 
 int /*<<< orphan*/ * start_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static tree
cp_parser_omp_for_loop (cp_parser *parser)
{
  tree init, cond, incr, body, decl, pre_body;
  location_t loc;

  if (!cp_lexer_next_token_is_keyword (parser->lexer, RID_FOR))
    {
      cp_parser_error (parser, "for statement expected");
      return NULL;
    }
  loc = cp_lexer_consume_token (parser->lexer)->location;
  if (!cp_parser_require (parser, CPP_OPEN_PAREN, "`('"))
    return NULL;

  init = decl = NULL;
  pre_body = push_stmt_list ();
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
    {
      cp_decl_specifier_seq type_specifiers;

      /* First, try to parse as an initialized declaration.  See
	 cp_parser_condition, from whence the bulk of this is copied.  */

      cp_parser_parse_tentatively (parser);
      cp_parser_type_specifier_seq (parser, /*is_condition=*/false,
				    &type_specifiers);
      if (!cp_parser_error_occurred (parser))
	{
	  tree asm_specification, attributes;
	  cp_declarator *declarator;

	  declarator = cp_parser_declarator (parser,
					     CP_PARSER_DECLARATOR_NAMED,
					     /*ctor_dtor_or_conv_p=*/NULL,
					     /*parenthesized_p=*/NULL,
					     /*member_p=*/false);
	  attributes = cp_parser_attributes_opt (parser);
	  asm_specification = cp_parser_asm_specification_opt (parser);

	  cp_parser_require (parser, CPP_EQ, "`='");
	  if (cp_parser_parse_definitely (parser))
	    {
	      tree pushed_scope;

	      decl = start_decl (declarator, &type_specifiers,
				 /*initialized_p=*/false, attributes,
				 /*prefix_attributes=*/NULL_TREE,
				 &pushed_scope);

	      init = cp_parser_assignment_expression (parser, false);

	      cp_finish_decl (decl, NULL_TREE, /*init_const_expr_p=*/false,
			      asm_specification, LOOKUP_ONLYCONVERTING);

	      if (pushed_scope)
		pop_scope (pushed_scope);
	    }
	}
      else
	cp_parser_abort_tentative_parse (parser);

      /* If parsing as an initialized declaration failed, try again as
	 a simple expression.  */
      if (decl == NULL)
	init = cp_parser_expression (parser, false);
    }
  cp_parser_require (parser, CPP_SEMICOLON, "`;'");
  pre_body = pop_stmt_list (pre_body);

  cond = NULL;
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
    cond = cp_parser_condition (parser);
  cp_parser_require (parser, CPP_SEMICOLON, "`;'");

  incr = NULL;
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_CLOSE_PAREN))
    incr = cp_parser_expression (parser, false);

  if (!cp_parser_require (parser, CPP_CLOSE_PAREN, "`)'"))
    cp_parser_skip_to_closing_parenthesis (parser, /*recovering=*/true,
					   /*or_comma=*/false,
					   /*consume_paren=*/true);

  /* Note that we saved the original contents of this flag when we entered
     the structured block, and so we don't need to re-save it here.  */
  parser->in_statement = IN_OMP_FOR;

  /* Note that the grammar doesn't call for a structured block here,
     though the loop as a whole is a structured block.  */
  body = push_stmt_list ();
  cp_parser_statement (parser, NULL_TREE, false, NULL);
  body = pop_stmt_list (body);

  return finish_omp_for (loc, decl, init, cond, incr, body, pre_body);
}