#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  num_template_parameter_lists; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
struct TYPE_10__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_GREATER ; 
 scalar_t__ CPP_LESS ; 
 int /*<<< orphan*/  RID_TEMPLATE ; 
 int /*<<< orphan*/  begin_specialization () ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_single_declaration (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_block_or_statement (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_template_declaration_after_export (TYPE_1__*,int) ; 
 scalar_t__ current_lang_name ; 
 int /*<<< orphan*/  end_specialization () ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ lang_name_c ; 
 int /*<<< orphan*/  lang_name_cplusplus ; 
 int /*<<< orphan*/  pop_lang_context () ; 
 int /*<<< orphan*/  push_lang_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_explicit_specialization (cp_parser* parser)
{
  bool need_lang_pop;
  /* Look for the `template' keyword.  */
  cp_parser_require_keyword (parser, RID_TEMPLATE, "`template'");
  /* Look for the `<'.  */
  cp_parser_require (parser, CPP_LESS, "`<'");
  /* Look for the `>'.  */
  cp_parser_require (parser, CPP_GREATER, "`>'");
  /* We have processed another parameter list.  */
  ++parser->num_template_parameter_lists;
  /* [temp]

     A template ... explicit specialization ... shall not have C
     linkage.  */
  if (current_lang_name == lang_name_c)
    {
      error ("template specialization with C linkage");
      /* Give it C++ linkage to avoid confusing other parts of the
	 front end.  */
      push_lang_context (lang_name_cplusplus);
      need_lang_pop = true;
    }
  else
    need_lang_pop = false;
  /* Let the front end know that we are beginning a specialization.  */
  if (!begin_specialization ())
    {
      end_specialization ();
      cp_parser_skip_to_end_of_block_or_statement (parser);
      return;
    }

  /* If the next keyword is `template', we need to figure out whether
     or not we're looking a template-declaration.  */
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_TEMPLATE))
    {
      if (cp_lexer_peek_nth_token (parser->lexer, 2)->type == CPP_LESS
	  && cp_lexer_peek_nth_token (parser->lexer, 3)->type != CPP_GREATER)
	cp_parser_template_declaration_after_export (parser,
						     /*member_p=*/false);
      else
	cp_parser_explicit_specialization (parser);
    }
  else
    /* Parse the dependent declaration.  */
    cp_parser_single_declaration (parser,
				  /*checks=*/NULL,
				  /*member_p=*/false,
				  /*friend_p=*/NULL);
  /* We're done with the specialization.  */
  end_specialization ();
  /* For the erroneous case of a template with C linkage, we pushed an
     implicit C++ linkage scope; exit that scope now.  */
  if (need_lang_pop)
    pop_lang_context ();
  /* We're done with this parameter list.  */
  --parser->num_template_parameter_lists;
}