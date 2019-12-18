#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_9__ {int in_unbraced_linkage_specification_p; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  RID_EXTERN ; 
 int TREE_STRING_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_declaration (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_declaration_seq_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_string_literal (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  get_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lang_name_cplusplus ; 
 int /*<<< orphan*/  pop_lang_context () ; 
 int /*<<< orphan*/  push_lang_context (int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_linkage_specification (cp_parser* parser)
{
  tree linkage;

  /* Look for the `extern' keyword.  */
  cp_parser_require_keyword (parser, RID_EXTERN, "`extern'");

  /* Look for the string-literal.  */
  linkage = cp_parser_string_literal (parser, false, false);

  /* Transform the literal into an identifier.  If the literal is a
     wide-character string, or contains embedded NULs, then we can't
     handle it as the user wants.  */
  if (strlen (TREE_STRING_POINTER (linkage))
      != (size_t) (TREE_STRING_LENGTH (linkage) - 1))
    {
      cp_parser_error (parser, "invalid linkage-specification");
      /* Assume C++ linkage.  */
      linkage = lang_name_cplusplus;
    }
  else
    linkage = get_identifier (TREE_STRING_POINTER (linkage));

  /* We're now using the new linkage.  */
  push_lang_context (linkage);

  /* If the next token is a `{', then we're using the first
     production.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
    {
      /* Consume the `{' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the declarations.  */
      cp_parser_declaration_seq_opt (parser);
      /* Look for the closing `}'.  */
      cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");
    }
  /* Otherwise, there's just one declaration.  */
  else
    {
      bool saved_in_unbraced_linkage_specification_p;

      saved_in_unbraced_linkage_specification_p
	= parser->in_unbraced_linkage_specification_p;
      parser->in_unbraced_linkage_specification_p = true;
      cp_parser_declaration (parser);
      parser->in_unbraced_linkage_specification_p
	= saved_in_unbraced_linkage_specification_p;
    }

  /* We're done with the linkage-specification.  */
  pop_lang_context ();
}