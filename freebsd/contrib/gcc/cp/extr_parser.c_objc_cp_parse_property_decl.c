#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_7__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_decl_specifier_seq ;

/* Variables and functions */
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_EOF ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_NAMED ; 
 int /*<<< orphan*/  CP_PARSER_FLAGS_NONE ; 
 int /*<<< orphan*/  NORMAL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  copy_node (scalar_t__) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_decl_specifier_seq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * cp_parser_declarator (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ grokdeclarator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objc_add_property_variable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
objc_cp_parse_property_decl (cp_parser *parser)
{
  int declares_class_or_enum;
  cp_decl_specifier_seq declspecs;
  
  cp_parser_decl_specifier_seq (parser,
						  CP_PARSER_FLAGS_NONE,
						  &declspecs,
						  &declares_class_or_enum);
  /* Keep going until we hit the `;' at the end of the declaration. */
  while (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
    {
      tree property;
      cp_token *token;
      cp_declarator *declarator
      = cp_parser_declarator (parser, CP_PARSER_DECLARATOR_NAMED,
						NULL, NULL, false);
      property = grokdeclarator (declarator, &declspecs, NORMAL,0, NULL);
      /* Revover from any kind of error in property declaration. */
      if (property == error_mark_node || property == NULL_TREE)
	return;
      /* Add to property list. */
      objc_add_property_variable (copy_node (property));
      if (token->type == CPP_COMMA)
      {
	cp_lexer_consume_token (parser->lexer);  /* Eat ','.  */
	continue;
      }
      else if (token->type == CPP_EOF)
	return;
    }
    cp_lexer_consume_token (parser->lexer);  /* Eat ';'.  */
}