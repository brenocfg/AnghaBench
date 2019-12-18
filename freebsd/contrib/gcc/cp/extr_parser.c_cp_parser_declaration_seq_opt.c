#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; scalar_t__ implicit_extern_c; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_8__ {int implicit_extern_c; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_BRACE ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_PRAGMA ; 
 scalar_t__ CPP_PRAGMA_EOL ; 
 scalar_t__ CPP_SEMICOLON ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_declaration (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_pragma (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/  lang_name_c ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  pop_lang_context () ; 
 int /*<<< orphan*/  pragma_external ; 
 int /*<<< orphan*/  push_lang_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_declaration_seq_opt (cp_parser* parser)
{
  while (true)
    {
      cp_token *token;

      token = cp_lexer_peek_token (parser->lexer);

      if (token->type == CPP_CLOSE_BRACE
	  || token->type == CPP_EOF
	  || token->type == CPP_PRAGMA_EOL)
	break;

      if (token->type == CPP_SEMICOLON)
	{
	  /* A declaration consisting of a single semicolon is
	     invalid.  Allow it unless we're being pedantic.  */
	  cp_lexer_consume_token (parser->lexer);
	  if (pedantic && !in_system_header)
	    pedwarn ("extra %<;%>");
	  continue;
	}

      /* If we're entering or exiting a region that's implicitly
	 extern "C", modify the lang context appropriately.  */
      if (!parser->implicit_extern_c && token->implicit_extern_c)
	{
	  push_lang_context (lang_name_c);
	  parser->implicit_extern_c = true;
	}
      else if (parser->implicit_extern_c && !token->implicit_extern_c)
	{
	  pop_lang_context ();
	  parser->implicit_extern_c = false;
	}

      if (token->type == CPP_PRAGMA)
	{
	  /* A top-level declaration can consist solely of a #pragma.
	     A nested declaration cannot, so this is done here and not
	     in cp_parser_declaration.  (A #pragma at block scope is
	     handled in cp_parser_statement.)  */
	  cp_parser_pragma (parser, pragma_external);
	  continue;
	}

      /* Parse the declaration itself.  */
      cp_parser_declaration (parser);
    }
}