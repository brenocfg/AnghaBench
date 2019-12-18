#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_12__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_13__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_EQ ; 
 int /*<<< orphan*/  CPP_GREATER ; 
 int /*<<< orphan*/  CPP_KEYWORD ; 
 int /*<<< orphan*/  CPP_LESS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_CLASS 130 
#define  RID_TEMPLATE 129 
#define  RID_TYPENAME 128 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DECL ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_template_template_default_arg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_type_node ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_id_expression (TYPE_2__*,int,int,int*,int,int) ; 
 int /*<<< orphan*/  cp_parser_identifier (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_lookup_name (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_2__*,int const,char*) ; 
 int /*<<< orphan*/  cp_parser_template_parameter_list (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_type_id (TYPE_2__*) ; 
 int /*<<< orphan*/  dk_no_deferred ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_template_template_parm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_template_type_parm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  none_type ; 
 int /*<<< orphan*/  pop_deferring_access_checks () ; 
 int /*<<< orphan*/  push_deferring_access_checks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_type_parameter (cp_parser* parser)
{
  cp_token *token;
  tree parameter;

  /* Look for a keyword to tell us what kind of parameter this is.  */
  token = cp_parser_require (parser, CPP_KEYWORD,
			     "`class', `typename', or `template'");
  if (!token)
    return error_mark_node;

  switch (token->keyword)
    {
    case RID_CLASS:
    case RID_TYPENAME:
      {
	tree identifier;
	tree default_argument;

	/* If the next token is an identifier, then it names the
	   parameter.  */
	if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
	  identifier = cp_parser_identifier (parser);
	else
	  identifier = NULL_TREE;

	/* Create the parameter.  */
	parameter = finish_template_type_parm (class_type_node, identifier);

	/* If the next token is an `=', we have a default argument.  */
	if (cp_lexer_next_token_is (parser->lexer, CPP_EQ))
	  {
	    /* Consume the `=' token.  */
	    cp_lexer_consume_token (parser->lexer);
	    /* Parse the default-argument.  */
	    push_deferring_access_checks (dk_no_deferred);
	    default_argument = cp_parser_type_id (parser);
	    pop_deferring_access_checks ();
	  }
	else
	  default_argument = NULL_TREE;

	/* Create the combined representation of the parameter and the
	   default argument.  */
	parameter = build_tree_list (default_argument, parameter);
      }
      break;

    case RID_TEMPLATE:
      {
	tree parameter_list;
	tree identifier;
	tree default_argument;

	/* Look for the `<'.  */
	cp_parser_require (parser, CPP_LESS, "`<'");
	/* Parse the template-parameter-list.  */
	parameter_list = cp_parser_template_parameter_list (parser);
	/* Look for the `>'.  */
	cp_parser_require (parser, CPP_GREATER, "`>'");
	/* Look for the `class' keyword.  */
	cp_parser_require_keyword (parser, RID_CLASS, "`class'");
	/* If the next token is an `=', then there is a
	   default-argument.  If the next token is a `>', we are at
	   the end of the parameter-list.  If the next token is a `,',
	   then we are at the end of this parameter.  */
	if (cp_lexer_next_token_is_not (parser->lexer, CPP_EQ)
	    && cp_lexer_next_token_is_not (parser->lexer, CPP_GREATER)
	    && cp_lexer_next_token_is_not (parser->lexer, CPP_COMMA))
	  {
	    identifier = cp_parser_identifier (parser);
	    /* Treat invalid names as if the parameter were nameless.  */
	    if (identifier == error_mark_node)
	      identifier = NULL_TREE;
	  }
	else
	  identifier = NULL_TREE;

	/* Create the template parameter.  */
	parameter = finish_template_template_parm (class_type_node,
						   identifier);

	/* If the next token is an `=', then there is a
	   default-argument.  */
	if (cp_lexer_next_token_is (parser->lexer, CPP_EQ))
	  {
	    bool is_template;

	    /* Consume the `='.  */
	    cp_lexer_consume_token (parser->lexer);
	    /* Parse the id-expression.  */
	    push_deferring_access_checks (dk_no_deferred);
	    default_argument
	      = cp_parser_id_expression (parser,
					 /*template_keyword_p=*/false,
					 /*check_dependency_p=*/true,
					 /*template_p=*/&is_template,
					 /*declarator_p=*/false,
					 /*optional_p=*/false);
	    if (TREE_CODE (default_argument) == TYPE_DECL)
	      /* If the id-expression was a template-id that refers to
		 a template-class, we already have the declaration here,
		 so no further lookup is needed.  */
		 ;
	    else
	      /* Look up the name.  */
	      default_argument
		= cp_parser_lookup_name (parser, default_argument,
					 none_type,
					 /*is_template=*/is_template,
					 /*is_namespace=*/false,
					 /*check_dependency=*/true,
					 /*ambiguous_decls=*/NULL);
	    /* See if the default argument is valid.  */
	    default_argument
	      = check_template_template_default_arg (default_argument);
	    pop_deferring_access_checks ();
	  }
	else
	  default_argument = NULL_TREE;

	/* Create the combined representation of the parameter and the
	   default argument.  */
	parameter = build_tree_list (default_argument, parameter);
      }
      break;

    default:
      gcc_unreachable ();
      break;
    }

  return parameter;
}