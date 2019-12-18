#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int implicit_extern_c; int /*<<< orphan*/ * lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_EOF ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  cdk_error ; 
 scalar_t__ cp_error_declarator ; 
 int /*<<< orphan*/  cp_lexer_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_declaration_seq_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  declarator_obstack ; 
 int /*<<< orphan*/  finish_translation_unit () ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 scalar_t__ make_declarator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_parameter_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_parameters ; 
 void* obstack_next_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_lang_context () ; 

__attribute__((used)) static bool
cp_parser_translation_unit (cp_parser* parser)
{
  /* The address of the first non-permanent object on the declarator
     obstack.  */
  static void *declarator_obstack_base;

  bool success;

  /* Create the declarator obstack, if necessary.  */
  if (!cp_error_declarator)
    {
      gcc_obstack_init (&declarator_obstack);
      /* Create the error declarator.  */
      cp_error_declarator = make_declarator (cdk_error);
      /* Create the empty parameter list.  */
      no_parameters = make_parameter_declarator (NULL, NULL, NULL_TREE);
      /* Remember where the base of the declarator obstack lies.  */
      declarator_obstack_base = obstack_next_free (&declarator_obstack);
    }

  cp_parser_declaration_seq_opt (parser);

  /* If there are no tokens left then all went well.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_EOF))
    {
      /* Get rid of the token array; we don't need it any more.  */
      cp_lexer_destroy (parser->lexer);
      parser->lexer = NULL;

      /* This file might have been a context that's implicitly extern
	 "C".  If so, pop the lang context.  (Only relevant for PCH.) */
      if (parser->implicit_extern_c)
	{
	  pop_lang_context ();
	  parser->implicit_extern_c = false;
	}

      /* Finish up.  */
      finish_translation_unit ();

      success = true;
    }
  else
    {
      cp_parser_error (parser, "expected declaration");
      success = false;
    }

  /* Make sure the declarator obstack was fully cleaned up.  */
  gcc_assert (obstack_next_free (&declarator_obstack)
	      == declarator_obstack_base);

  /* All went well.  */
  return success;
}