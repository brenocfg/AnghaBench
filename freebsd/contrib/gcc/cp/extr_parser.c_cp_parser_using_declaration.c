#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_17__ {scalar_t__ keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_18__ {int /*<<< orphan*/  scope; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 scalar_t__ BIT_NOT_EXPR ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RID_TYPENAME ; 
 int /*<<< orphan*/  RID_USING ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ at_class_scope_p () ; 
 int /*<<< orphan*/  at_namespace_scope_p () ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_error_occurred (TYPE_2__*) ; 
 scalar_t__ cp_parser_global_scope_opt (TYPE_2__*,int) ; 
 scalar_t__ cp_parser_lookup_name_simple (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_name_lookup_error (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_nested_name_specifier (TYPE_2__*,int,int,int,int) ; 
 scalar_t__ cp_parser_nested_name_specifier_opt (TYPE_2__*,int,int,int,int) ; 
 int cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_2__*) ; 
 scalar_t__ cp_parser_unqualified_id (TYPE_2__*,int,int,int,int) ; 
 scalar_t__ do_class_using_decl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  do_local_using_decl (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_toplevel_using_decl (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_member_declaration (scalar_t__) ; 
 scalar_t__ global_namespace ; 

__attribute__((used)) static bool
cp_parser_using_declaration (cp_parser* parser, 
			     bool access_declaration_p)
{
  cp_token *token;
  bool typename_p = false;
  bool global_scope_p;
  tree decl;
  tree identifier;
  tree qscope;

  if (access_declaration_p)
    cp_parser_parse_tentatively (parser);
  else
    {
      /* Look for the `using' keyword.  */
      cp_parser_require_keyword (parser, RID_USING, "`using'");
      
      /* Peek at the next token.  */
      token = cp_lexer_peek_token (parser->lexer);
      /* See if it's `typename'.  */
      if (token->keyword == RID_TYPENAME)
	{
	  /* Remember that we've seen it.  */
	  typename_p = true;
	  /* Consume the `typename' token.  */
	  cp_lexer_consume_token (parser->lexer);
	}
    }

  /* Look for the optional global scope qualification.  */
  global_scope_p
    = (cp_parser_global_scope_opt (parser,
				   /*current_scope_valid_p=*/false)
       != NULL_TREE);

  /* If we saw `typename', or didn't see `::', then there must be a
     nested-name-specifier present.  */
  if (typename_p || !global_scope_p)
    qscope = cp_parser_nested_name_specifier (parser, typename_p,
					      /*check_dependency_p=*/true,
					      /*type_p=*/false,
					      /*is_declaration=*/true);
  /* Otherwise, we could be in either of the two productions.  In that
     case, treat the nested-name-specifier as optional.  */
  else
    qscope = cp_parser_nested_name_specifier_opt (parser,
						  /*typename_keyword_p=*/false,
						  /*check_dependency_p=*/true,
						  /*type_p=*/false,
						  /*is_declaration=*/true);
  if (!qscope)
    qscope = global_namespace;

  if (access_declaration_p && cp_parser_error_occurred (parser))
    /* Something has already gone wrong; there's no need to parse
       further.  Since an error has occurred, the return value of
       cp_parser_parse_definitely will be false, as required.  */
    return cp_parser_parse_definitely (parser);

  /* Parse the unqualified-id.  */
  identifier = cp_parser_unqualified_id (parser,
					 /*template_keyword_p=*/false,
					 /*check_dependency_p=*/true,
					 /*declarator_p=*/true,
					 /*optional_p=*/false);

  if (access_declaration_p)
    {
      if (cp_lexer_next_token_is_not (parser->lexer, CPP_SEMICOLON))
	cp_parser_simulate_error (parser);
      if (!cp_parser_parse_definitely (parser))
	return false;
    }

  /* The function we call to handle a using-declaration is different
     depending on what scope we are in.  */
  if (qscope == error_mark_node || identifier == error_mark_node)
    ;
  else if (TREE_CODE (identifier) != IDENTIFIER_NODE
	   && TREE_CODE (identifier) != BIT_NOT_EXPR)
    /* [namespace.udecl]

       A using declaration shall not name a template-id.  */
    error ("a template-id may not appear in a using-declaration");
  else
    {
      if (at_class_scope_p ())
	{
	  /* Create the USING_DECL.  */
	  decl = do_class_using_decl (parser->scope, identifier);
	  /* Add it to the list of members in this class.  */
	  finish_member_declaration (decl);
	}
      else
	{
	  decl = cp_parser_lookup_name_simple (parser, identifier);
	  if (decl == error_mark_node)
	    cp_parser_name_lookup_error (parser, identifier, decl, NULL);
	  else if (!at_namespace_scope_p ())
	    do_local_using_decl (decl, qscope, identifier);
	  else
	    do_toplevel_using_decl (decl, qscope, identifier);
	}
    }

  /* Look for the final `;'.  */
  cp_parser_require (parser, CPP_SEMICOLON, "`;'");
  
  return true;
}