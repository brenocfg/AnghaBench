#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_10__ {scalar_t__ keyword; scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_11__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_12__ {int /*<<< orphan*/  default_argument; int /*<<< orphan*/  decl_specifiers; int /*<<< orphan*/  declarator; } ;
typedef  TYPE_3__ cp_parameter_declarator ;

/* Variables and functions */
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_EQ ; 
 scalar_t__ CPP_GREATER ; 
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  PARM ; 
 scalar_t__ RID_CLASS ; 
 scalar_t__ RID_TEMPLATE ; 
 scalar_t__ RID_TYPENAME ; 
 scalar_t__ build_tree_list (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 TYPE_3__* cp_parser_parameter_declaration (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_type_parameter (TYPE_2__*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ grokdeclarator (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
cp_parser_template_parameter (cp_parser* parser, bool *is_non_type)
{
  cp_token *token;
  cp_parameter_declarator *parameter_declarator;
  tree parm;

  /* Assume it is a type parameter or a template parameter.  */
  *is_non_type = false;
  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  /* If it is `class' or `template', we have a type-parameter.  */
  if (token->keyword == RID_TEMPLATE)
    return cp_parser_type_parameter (parser);
  /* If it is `class' or `typename' we do not know yet whether it is a
     type parameter or a non-type parameter.  Consider:

       template <typename T, typename T::X X> ...

     or:

       template <class C, class D*> ...

     Here, the first parameter is a type parameter, and the second is
     a non-type parameter.  We can tell by looking at the token after
     the identifier -- if it is a `,', `=', or `>' then we have a type
     parameter.  */
  if (token->keyword == RID_TYPENAME || token->keyword == RID_CLASS)
    {
      /* Peek at the token after `class' or `typename'.  */
      token = cp_lexer_peek_nth_token (parser->lexer, 2);
      /* If it's an identifier, skip it.  */
      if (token->type == CPP_NAME)
	token = cp_lexer_peek_nth_token (parser->lexer, 3);
      /* Now, see if the token looks like the end of a template
	 parameter.  */
      if (token->type == CPP_COMMA
	  || token->type == CPP_EQ
	  || token->type == CPP_GREATER)
	return cp_parser_type_parameter (parser);
    }

  /* Otherwise, it is a non-type parameter.

     [temp.param]

     When parsing a default template-argument for a non-type
     template-parameter, the first non-nested `>' is taken as the end
     of the template parameter-list rather than a greater-than
     operator.  */
  *is_non_type = true;
  parameter_declarator
     = cp_parser_parameter_declaration (parser, /*template_parm_p=*/true,
					/*parenthesized_p=*/NULL);
  parm = grokdeclarator (parameter_declarator->declarator,
			 &parameter_declarator->decl_specifiers,
			 PARM, /*initialized=*/0,
			 /*attrlist=*/NULL);
  if (parm == error_mark_node)
    return error_mark_node;
  return build_tree_list (parameter_declarator->default_argument, parm);
}