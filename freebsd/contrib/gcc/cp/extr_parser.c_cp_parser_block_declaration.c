#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_15__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 scalar_t__ RID_ASM ; 
 scalar_t__ RID_LABEL ; 
 scalar_t__ RID_NAMESPACE ; 
 scalar_t__ RID_USING ; 
 TYPE_1__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_asm_definition (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_commit_to_tentative_parse (TYPE_2__*) ; 
 scalar_t__ cp_parser_extension_opt (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  cp_parser_label_declaration (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_namespace_alias_definition (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_simple_declaration (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_using_declaration (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_using_directive (TYPE_2__*) ; 
 int pedantic ; 

__attribute__((used)) static void
cp_parser_block_declaration (cp_parser *parser,
			     bool      statement_p)
{
  cp_token *token1;
  int saved_pedantic;

  /* Check for the `__extension__' keyword.  */
  if (cp_parser_extension_opt (parser, &saved_pedantic))
    {
      /* Parse the qualified declaration.  */
      cp_parser_block_declaration (parser, statement_p);
      /* Restore the PEDANTIC flag.  */
      pedantic = saved_pedantic;

      return;
    }

  /* Peek at the next token to figure out which kind of declaration is
     present.  */
  token1 = cp_lexer_peek_token (parser->lexer);

  /* If the next keyword is `asm', we have an asm-definition.  */
  if (token1->keyword == RID_ASM)
    {
      if (statement_p)
	cp_parser_commit_to_tentative_parse (parser);
      cp_parser_asm_definition (parser);
    }
  /* If the next keyword is `namespace', we have a
     namespace-alias-definition.  */
  else if (token1->keyword == RID_NAMESPACE)
    cp_parser_namespace_alias_definition (parser);
  /* If the next keyword is `using', we have either a
     using-declaration or a using-directive.  */
  else if (token1->keyword == RID_USING)
    {
      cp_token *token2;

      if (statement_p)
	cp_parser_commit_to_tentative_parse (parser);
      /* If the token after `using' is `namespace', then we have a
	 using-directive.  */
      token2 = cp_lexer_peek_nth_token (parser->lexer, 2);
      if (token2->keyword == RID_NAMESPACE)
	cp_parser_using_directive (parser);
      /* Otherwise, it's a using-declaration.  */
      else
	cp_parser_using_declaration (parser,
				     /*access_declaration_p=*/false);
    }
  /* If the next keyword is `__label__' we have a label declaration.  */
  else if (token1->keyword == RID_LABEL)
    {
      if (statement_p)
	cp_parser_commit_to_tentative_parse (parser);
      cp_parser_label_declaration (parser);
    }
  /* Anything else must be a simple-declaration.  */
  else
    cp_parser_simple_declaration (parser, !statement_p);
}