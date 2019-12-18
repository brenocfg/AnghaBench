#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
struct TYPE_15__ {scalar_t__ value; } ;
struct TYPE_16__ {scalar_t__ keyword; TYPE_1__ u; } ;
typedef  TYPE_2__ cp_token ;
struct TYPE_17__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_3__ cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_decl_specifier_seq ;
struct TYPE_14__ {int type; } ;

/* Variables and functions */
#define  CPP_MINUS 135 
#define  CPP_MINUS_MINUS 134 
#define  CPP_MULT 133 
#define  CPP_NAME 132 
#define  CPP_OPEN_PAREN 131 
#define  CPP_OPEN_SQUARE 130 
#define  CPP_PLUS 129 
#define  CPP_PLUS_PLUS 128 
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_NAMED ; 
 int /*<<< orphan*/  CP_PARSER_FLAGS_OPTIONAL ; 
 scalar_t__ IDENTIFIER_NODE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ RID_ENUM ; 
 scalar_t__ RID_IN ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  add_stmt (scalar_t__) ; 
 int /*<<< orphan*/  clear_decl_specs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cp_error_declarator ; 
 int /*<<< orphan*/  cp_finish_decl (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_13__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_abort_tentative_parse (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_commit_to_tentative_parse (TYPE_3__*) ; 
 int /*<<< orphan*/ * cp_parser_declarator (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cp_parser_expression (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_3__*) ; 
 scalar_t__ cp_parser_token_is_class_key (TYPE_2__*) ; 
 scalar_t__ cp_parser_type_specifier (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__* ridpointers ; 
 scalar_t__ start_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool
cp_parser_parse_foreach_stmt (cp_parser *parser)
{
  int decl_spec_declares_class_or_enum;
  bool is_cv_qualifier;
  tree type_spec;
  cp_decl_specifier_seq decl_specs;
  tree node;
  cp_token *token;
  bool is_legit_foreach = false;
  cp_declarator *declarator;

  /* Exclude class/struct/enum type definition in for-loop header, which is 
     aparently legal in c++. Otherwise, it causes side-effect (type is enterred
     in function's scope) when type is re-parsed. */
  token = cp_lexer_peek_token (parser->lexer);
  if (cp_parser_token_is_class_key (token) || token->keyword == RID_ENUM)
    return false;

  cp_parser_parse_tentatively (parser); 
  clear_decl_specs (&decl_specs);
  type_spec
    = cp_parser_type_specifier (parser, CP_PARSER_FLAGS_OPTIONAL,
				 &decl_specs,
				 /*is_declaration=*/true,
				 &decl_spec_declares_class_or_enum,
				 &is_cv_qualifier);
  declarator
    = cp_parser_declarator (parser, CP_PARSER_DECLARATOR_NAMED,
			     NULL,
			     /*parenthesized_p=*/NULL,
			     /*member_p=*/false);
  if (declarator == cp_error_declarator)
    {
      cp_parser_abort_tentative_parse (parser);
      return false;
    }

  token = cp_lexer_peek_token (parser->lexer);

  node = token->u.value; 
  if (node && TREE_CODE (node) == IDENTIFIER_NODE
      && node == ridpointers [(int) RID_IN])
    {   
      enum cpp_ttype nt = cp_lexer_peek_nth_token (parser->lexer, 2)->type;
      switch (nt)
	 {
	   case CPP_NAME:
	   case CPP_OPEN_PAREN:
	   case CPP_MULT:
	   case CPP_PLUS: case CPP_PLUS_PLUS:
	   case CPP_MINUS: case CPP_MINUS_MINUS:
	   case CPP_OPEN_SQUARE:
	      is_legit_foreach = true;
	       default:
	        break;
	 }
    }
  if (is_legit_foreach)
    {
      tree pushed_scope = NULL;
      tree decl;
      if (type_spec)
	{
	  /* we have: 'for (type selector in...)' */
	  cp_parser_commit_to_tentative_parse (parser);
	   decl = start_decl (declarator, &decl_specs,
			      false /*is_initialized*/,
			      NULL_TREE /*attributes*/,
			      NULL_TREE /*prefix_attributes*/,
			      &pushed_scope);
	   /* APPLE LOCAL begin radar 5130983 */
	   if (!decl || decl == error_mark_node)
	     {
	       error ("selector is undeclared");
	       is_legit_foreach = false;
	     }
	   else
	     cp_finish_decl (decl,
			     NULL_TREE /*initializer*/,
			    false /*init_const_expr_p=*/,
			     NULL_TREE /*asm_specification*/,
			     0 /*flags */);
	}
      else {
	 tree statement;
	 /* we have: 'for (selector in...)' */
	 /* Parse it as an expression. */
	 cp_parser_abort_tentative_parse (parser);
	 statement = cp_parser_expression (parser, /*cast_p=*/false);
	 add_stmt (statement);
      }
      /* APPLE LOCAL end radar 5130983 */
      /* Consume the 'in' token */
      cp_lexer_consume_token (parser->lexer);
    }
  else
    cp_parser_abort_tentative_parse (parser);
  return is_legit_foreach;
}