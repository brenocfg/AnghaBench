#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_19__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_20__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_21__ {scalar_t__ any_specifiers_p; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ cp_decl_specifier_seq ;

/* Variables and functions */
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 scalar_t__ CPP_SEMICOLON ; 
 int /*<<< orphan*/  CP_PARSER_FLAGS_OPTIONAL ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_commit_to_tentative_parse (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_decl_specifier_seq (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int*) ; 
 scalar_t__ cp_parser_declares_only_class_p (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 scalar_t__ cp_parser_error_occurred (TYPE_2__*) ; 
 scalar_t__ cp_parser_init_declarator (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int,int,int,int*) ; 
 scalar_t__ cp_parser_parse_and_diagnose_invalid_type_name (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_statement (TYPE_2__*) ; 
 scalar_t__ cp_parser_uncommitted_to_tentative_parse_p (TYPE_2__*) ; 
 int /*<<< orphan*/  dk_deferred ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  perform_deferred_access_checks () ; 
 int /*<<< orphan*/  pop_deferring_access_checks () ; 
 int /*<<< orphan*/  push_deferring_access_checks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_tag (TYPE_3__*) ; 
 int /*<<< orphan*/  stop_deferring_access_checks () ; 

__attribute__((used)) static void
cp_parser_simple_declaration (cp_parser* parser,
			      bool function_definition_allowed_p)
{
  cp_decl_specifier_seq decl_specifiers;
  int declares_class_or_enum;
  bool saw_declarator;

  /* Defer access checks until we know what is being declared; the
     checks for names appearing in the decl-specifier-seq should be
     done as if we were in the scope of the thing being declared.  */
  push_deferring_access_checks (dk_deferred);

  /* Parse the decl-specifier-seq.  We have to keep track of whether
     or not the decl-specifier-seq declares a named class or
     enumeration type, since that is the only case in which the
     init-declarator-list is allowed to be empty.

     [dcl.dcl]

     In a simple-declaration, the optional init-declarator-list can be
     omitted only when declaring a class or enumeration, that is when
     the decl-specifier-seq contains either a class-specifier, an
     elaborated-type-specifier, or an enum-specifier.  */
  cp_parser_decl_specifier_seq (parser,
				CP_PARSER_FLAGS_OPTIONAL,
				&decl_specifiers,
				&declares_class_or_enum);
  /* We no longer need to defer access checks.  */
  stop_deferring_access_checks ();

  /* In a block scope, a valid declaration must always have a
     decl-specifier-seq.  By not trying to parse declarators, we can
     resolve the declaration/expression ambiguity more quickly.  */
  if (!function_definition_allowed_p
      && !decl_specifiers.any_specifiers_p)
    {
      cp_parser_error (parser, "expected declaration");
      goto done;
    }

  /* If the next two tokens are both identifiers, the code is
     erroneous. The usual cause of this situation is code like:

       T t;

     where "T" should name a type -- but does not.  */
  if (!decl_specifiers.type
      && cp_parser_parse_and_diagnose_invalid_type_name (parser))
    {
      /* If parsing tentatively, we should commit; we really are
	 looking at a declaration.  */
      cp_parser_commit_to_tentative_parse (parser);
      /* Give up.  */
      goto done;
    }

  /* If we have seen at least one decl-specifier, and the next token
     is not a parenthesis, then we must be looking at a declaration.
     (After "int (" we might be looking at a functional cast.)  */
  if (decl_specifiers.any_specifiers_p
      && cp_lexer_next_token_is_not (parser->lexer, CPP_OPEN_PAREN))
    cp_parser_commit_to_tentative_parse (parser);

  /* Keep going until we hit the `;' at the end of the simple
     declaration.  */
  saw_declarator = false;
  while (cp_lexer_next_token_is_not (parser->lexer,
				     CPP_SEMICOLON))
    {
      cp_token *token;
      bool function_definition_p;
      tree decl;

      if (saw_declarator)
	{
	  /* If we are processing next declarator, coma is expected */
	  token = cp_lexer_peek_token (parser->lexer);
	  gcc_assert (token->type == CPP_COMMA);
	  cp_lexer_consume_token (parser->lexer);
	}
      else
	saw_declarator = true;

      /* Parse the init-declarator.  */
      decl = cp_parser_init_declarator (parser, &decl_specifiers,
					/*checks=*/NULL,
					function_definition_allowed_p,
					/*member_p=*/false,
					declares_class_or_enum,
					&function_definition_p);
      /* If an error occurred while parsing tentatively, exit quickly.
	 (That usually happens when in the body of a function; each
	 statement is treated as a declaration-statement until proven
	 otherwise.)  */
      if (cp_parser_error_occurred (parser))
	goto done;
      /* Handle function definitions specially.  */
      if (function_definition_p)
	{
	  /* If the next token is a `,', then we are probably
	     processing something like:

	       void f() {}, *p;

	     which is erroneous.  */
	  if (cp_lexer_next_token_is (parser->lexer, CPP_COMMA))
	    error ("mixing declarations and function-definitions is forbidden");
	  /* Otherwise, we're done with the list of declarators.  */
	  else
	    {
	      pop_deferring_access_checks ();
	      return;
	    }
	}
      /* The next token should be either a `,' or a `;'.  */
      token = cp_lexer_peek_token (parser->lexer);
      /* If it's a `,', there are more declarators to come.  */
      if (token->type == CPP_COMMA)
	/* will be consumed next time around */;
      /* If it's a `;', we are done.  */
      else if (token->type == CPP_SEMICOLON)
	break;
      /* Anything else is an error.  */
      else
	{
	  /* If we have already issued an error message we don't need
	     to issue another one.  */
	  if (decl != error_mark_node
	      || cp_parser_uncommitted_to_tentative_parse_p (parser))
	    cp_parser_error (parser, "expected %<,%> or %<;%>");
	  /* Skip tokens until we reach the end of the statement.  */
	  cp_parser_skip_to_end_of_statement (parser);
	  /* If the next token is now a `;', consume it.  */
	  if (cp_lexer_next_token_is (parser->lexer, CPP_SEMICOLON))
	    cp_lexer_consume_token (parser->lexer);
	  goto done;
	}
      /* After the first time around, a function-definition is not
	 allowed -- even if it was OK at first.  For example:

	   int i, f() {}

	 is not valid.  */
      function_definition_allowed_p = false;
    }

  /* Issue an error message if no declarators are present, and the
     decl-specifier-seq does not itself declare a class or
     enumeration.  */
  if (!saw_declarator)
    {
      if (cp_parser_declares_only_class_p (parser))
	shadow_tag (&decl_specifiers);
      /* Perform any deferred access checks.  */
      perform_deferred_access_checks ();
    }

  /* Consume the `;'.  */
  cp_parser_require (parser, CPP_SEMICOLON, "`;'");

 done:
  pop_deferring_access_checks ();
}