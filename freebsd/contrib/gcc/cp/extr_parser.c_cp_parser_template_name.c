#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  scalar_t__ cp_token_position ;
struct TYPE_13__ {scalar_t__ scope; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 scalar_t__ BASELINK_P (scalar_t__) ; 
 scalar_t__ CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_FUNCTION_TEMPLATE_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 int /*<<< orphan*/  RID_OPERATOR ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  constructor_name_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_purge_tokens_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cp_lexer_token_position (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cp_parser_enclosed_template_argument_list (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_1__*,char*) ; 
 scalar_t__ cp_parser_identifier (TYPE_1__*) ; 
 scalar_t__ cp_parser_lookup_name (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_nth_token_starts_template_argument_list_p (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_operator_function_id (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 scalar_t__ cp_parser_simulate_error (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_closing_parenthesis (TYPE_1__*,int,int,int) ; 
 scalar_t__ dependent_type_p (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  get_first_fn (scalar_t__) ; 
 int /*<<< orphan*/  inform (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ maybe_get_template_decl_from_type_decl (scalar_t__) ; 
 int /*<<< orphan*/  none_type ; 
 scalar_t__ processing_template_decl ; 

__attribute__((used)) static tree
cp_parser_template_name (cp_parser* parser,
			 bool template_keyword_p,
			 bool check_dependency_p,
			 bool is_declaration,
			 bool *is_identifier)
{
  tree identifier;
  tree decl;
  tree fns;

  /* If the next token is `operator', then we have either an
     operator-function-id or a conversion-function-id.  */
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_OPERATOR))
    {
      /* We don't know whether we're looking at an
	 operator-function-id or a conversion-function-id.  */
      cp_parser_parse_tentatively (parser);
      /* Try an operator-function-id.  */
      identifier = cp_parser_operator_function_id (parser);
      /* If that didn't work, try a conversion-function-id.  */
      if (!cp_parser_parse_definitely (parser))
	{
	  cp_parser_error (parser, "expected template-name");
	  return error_mark_node;
	}
    }
  /* Look for the identifier.  */
  else
    identifier = cp_parser_identifier (parser);

  /* If we didn't find an identifier, we don't have a template-id.  */
  if (identifier == error_mark_node)
    return error_mark_node;

  /* If the name immediately followed the `template' keyword, then it
     is a template-name.  However, if the next token is not `<', then
     we do not treat it as a template-name, since it is not being used
     as part of a template-id.  This enables us to handle constructs
     like:

       template <typename T> struct S { S(); };
       template <typename T> S<T>::S();

     correctly.  We would treat `S' as a template -- if it were `S<T>'
     -- but we do not if there is no `<'.  */

  if (processing_template_decl
      && cp_parser_nth_token_starts_template_argument_list_p (parser, 1))
    {
      /* In a declaration, in a dependent context, we pretend that the
	 "template" keyword was present in order to improve error
	 recovery.  For example, given:

	   template <typename T> void f(T::X<int>);

	 we want to treat "X<int>" as a template-id.  */
      if (is_declaration
	  && !template_keyword_p
	  && parser->scope && TYPE_P (parser->scope)
	  && check_dependency_p
	  && dependent_type_p (parser->scope)
	  /* Do not do this for dtors (or ctors), since they never
	     need the template keyword before their name.  */
	  && !constructor_name_p (identifier, parser->scope))
	{
	  cp_token_position start = 0;

	  /* Explain what went wrong.  */
	  error ("non-template %qD used as template", identifier);
	  inform ("use %<%T::template %D%> to indicate that it is a template",
		  parser->scope, identifier);
	  /* If parsing tentatively, find the location of the "<" token.  */
	  if (cp_parser_simulate_error (parser))
	    start = cp_lexer_token_position (parser->lexer, true);
	  /* Parse the template arguments so that we can issue error
	     messages about them.  */
	  cp_lexer_consume_token (parser->lexer);
	  cp_parser_enclosed_template_argument_list (parser);
	  /* Skip tokens until we find a good place from which to
	     continue parsing.  */
	  cp_parser_skip_to_closing_parenthesis (parser,
						 /*recovering=*/true,
						 /*or_comma=*/true,
						 /*consume_paren=*/false);
	  /* If parsing tentatively, permanently remove the
	     template argument list.  That will prevent duplicate
	     error messages from being issued about the missing
	     "template" keyword.  */
	  if (start)
	    cp_lexer_purge_tokens_after (parser->lexer, start);
	  if (is_identifier)
	    *is_identifier = true;
	  return identifier;
	}

      /* If the "template" keyword is present, then there is generally
	 no point in doing name-lookup, so we just return IDENTIFIER.
	 But, if the qualifying scope is non-dependent then we can
	 (and must) do name-lookup normally.  */
      if (template_keyword_p
	  && (!parser->scope
	      || (TYPE_P (parser->scope)
		  && dependent_type_p (parser->scope))))
	return identifier;
    }

  /* Look up the name.  */
  decl = cp_parser_lookup_name (parser, identifier,
				none_type,
				/*is_template=*/false,
				/*is_namespace=*/false,
				check_dependency_p,
				/*ambiguous_decls=*/NULL);
  decl = maybe_get_template_decl_from_type_decl (decl);

  /* If DECL is a template, then the name was a template-name.  */
  if (TREE_CODE (decl) == TEMPLATE_DECL)
    ;
  else
    {
      tree fn = NULL_TREE;

      /* The standard does not explicitly indicate whether a name that
	 names a set of overloaded declarations, some of which are
	 templates, is a template-name.  However, such a name should
	 be a template-name; otherwise, there is no way to form a
	 template-id for the overloaded templates.  */
      fns = BASELINK_P (decl) ? BASELINK_FUNCTIONS (decl) : decl;
      if (TREE_CODE (fns) == OVERLOAD)
	for (fn = fns; fn; fn = OVL_NEXT (fn))
	  if (TREE_CODE (OVL_CURRENT (fn)) == TEMPLATE_DECL)
	    break;

      if (!fn)
	{
	  /* The name does not name a template.  */
	  cp_parser_error (parser, "expected template-name");
	  return error_mark_node;
	}
    }

  /* If DECL is dependent, and refers to a function, then just return
     its name; we will look it up again during template instantiation.  */
  if (DECL_FUNCTION_TEMPLATE_P (decl) || !DECL_P (decl))
    {
      tree scope = CP_DECL_CONTEXT (get_first_fn (decl));
      if (TYPE_P (scope) && dependent_type_p (scope))
	return identifier;
    }

  return decl;
}