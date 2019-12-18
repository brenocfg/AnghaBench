#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  char* tree ;
struct TYPE_18__ {int /*<<< orphan*/  value; } ;
struct TYPE_19__ {int type; int /*<<< orphan*/  keyword; TYPE_1__ u; } ;
typedef  TYPE_2__ cp_token ;
struct TYPE_20__ {char* scope; char* object_scope; char* qualifying_scope; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_3__ cp_parser ;
struct TYPE_17__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_NOT_EXPR ; 
#define  CPP_COMPL 131 
#define  CPP_KEYWORD 130 
#define  CPP_NAME 129 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
#define  CPP_TEMPLATE_ID 128 
 int /*<<< orphan*/  DECL_IMPLICIT_TYPEDEF_P (char*) ; 
 int /*<<< orphan*/  DECL_SELF_REFERENCE_P (char*) ; 
 int /*<<< orphan*/  NAMESPACE_DECL ; 
 char* NULL_TREE ; 
 int /*<<< orphan*/  RID_OPERATOR ; 
 int /*<<< orphan*/  TREE_CODE (char*) ; 
 char* TREE_TYPE (char*) ; 
 int /*<<< orphan*/  TYPE_P (char*) ; 
 char* build_nt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_dtor_name (char*,char*) ; 
 int /*<<< orphan*/  constructor_name_p (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is (int /*<<< orphan*/ ,int const) ; 
 TYPE_16__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 char* cp_parser_class_name (TYPE_3__*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 char* cp_parser_conversion_function_id (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_3__*,char*) ; 
 char* cp_parser_identifier (TYPE_3__*) ; 
 char* cp_parser_operator_function_id (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_3__*) ; 
 char* cp_parser_template_id (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_uncommitted_to_tentative_parse_p (TYPE_3__*) ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 char* error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  none_type ; 

__attribute__((used)) static tree
cp_parser_unqualified_id (cp_parser* parser,
			  bool template_keyword_p,
			  bool check_dependency_p,
			  bool declarator_p,
			  bool optional_p)
{
  cp_token *token;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);

  switch (token->type)
    {
    case CPP_NAME:
      {
	tree id;

	/* We don't know yet whether or not this will be a
	   template-id.  */
	cp_parser_parse_tentatively (parser);
	/* Try a template-id.  */
	id = cp_parser_template_id (parser, template_keyword_p,
				    check_dependency_p,
				    declarator_p);
	/* If it worked, we're done.  */
	if (cp_parser_parse_definitely (parser))
	  return id;
	/* Otherwise, it's an ordinary identifier.  */
	return cp_parser_identifier (parser);
      }

    case CPP_TEMPLATE_ID:
      return cp_parser_template_id (parser, template_keyword_p,
				    check_dependency_p,
				    declarator_p);

    case CPP_COMPL:
      {
	tree type_decl;
	tree qualifying_scope;
	tree object_scope;
	tree scope;
	bool done;

	/* Consume the `~' token.  */
	cp_lexer_consume_token (parser->lexer);
	/* Parse the class-name.  The standard, as written, seems to
	   say that:

	     template <typename T> struct S { ~S (); };
	     template <typename T> S<T>::~S() {}

	   is invalid, since `~' must be followed by a class-name, but
	   `S<T>' is dependent, and so not known to be a class.
	   That's not right; we need to look in uninstantiated
	   templates.  A further complication arises from:

	     template <typename T> void f(T t) {
	       t.T::~T();
	     }

	   Here, it is not possible to look up `T' in the scope of `T'
	   itself.  We must look in both the current scope, and the
	   scope of the containing complete expression.

	   Yet another issue is:

	     struct S {
	       int S;
	       ~S();
	     };

	     S::~S() {}

	   The standard does not seem to say that the `S' in `~S'
	   should refer to the type `S' and not the data member
	   `S::S'.  */

	/* DR 244 says that we look up the name after the "~" in the
	   same scope as we looked up the qualifying name.  That idea
	   isn't fully worked out; it's more complicated than that.  */
	scope = parser->scope;
	object_scope = parser->object_scope;
	qualifying_scope = parser->qualifying_scope;

	/* Check for invalid scopes.  */
	if (scope == error_mark_node)
	  {
	    if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
	      cp_lexer_consume_token (parser->lexer);
	    return error_mark_node;
	  }
	if (scope && TREE_CODE (scope) == NAMESPACE_DECL)
	  {
	    if (!cp_parser_uncommitted_to_tentative_parse_p (parser))
	      error ("scope %qT before %<~%> is not a class-name", scope);
	    cp_parser_simulate_error (parser);
	    if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
	      cp_lexer_consume_token (parser->lexer);
	    return error_mark_node;
	  }
	gcc_assert (!scope || TYPE_P (scope));

	/* If the name is of the form "X::~X" it's OK.  */
	token = cp_lexer_peek_token (parser->lexer);
	if (scope
	    && token->type == CPP_NAME
	    && (cp_lexer_peek_nth_token (parser->lexer, 2)->type
		== CPP_OPEN_PAREN)
	    && constructor_name_p (token->u.value, scope))
	  {
	    cp_lexer_consume_token (parser->lexer);
	    return build_nt (BIT_NOT_EXPR, scope);
	  }

	/* If there was an explicit qualification (S::~T), first look
	   in the scope given by the qualification (i.e., S).  */
	done = false;
	type_decl = NULL_TREE;
	if (scope)
	  {
	    cp_parser_parse_tentatively (parser);
	    type_decl = cp_parser_class_name (parser,
					      /*typename_keyword_p=*/false,
					      /*template_keyword_p=*/false,
					      none_type,
					      /*check_dependency=*/false,
					      /*class_head_p=*/false,
					      declarator_p);
	    if (cp_parser_parse_definitely (parser))
	      done = true;
	  }
	/* In "N::S::~S", look in "N" as well.  */
	if (!done && scope && qualifying_scope)
	  {
	    cp_parser_parse_tentatively (parser);
	    parser->scope = qualifying_scope;
	    parser->object_scope = NULL_TREE;
	    parser->qualifying_scope = NULL_TREE;
	    type_decl
	      = cp_parser_class_name (parser,
				      /*typename_keyword_p=*/false,
				      /*template_keyword_p=*/false,
				      none_type,
				      /*check_dependency=*/false,
				      /*class_head_p=*/false,
				      declarator_p);
	    if (cp_parser_parse_definitely (parser))
	      done = true;
	  }
	/* In "p->S::~T", look in the scope given by "*p" as well.  */
	else if (!done && object_scope)
	  {
	    cp_parser_parse_tentatively (parser);
	    parser->scope = object_scope;
	    parser->object_scope = NULL_TREE;
	    parser->qualifying_scope = NULL_TREE;
	    type_decl
	      = cp_parser_class_name (parser,
				      /*typename_keyword_p=*/false,
				      /*template_keyword_p=*/false,
				      none_type,
				      /*check_dependency=*/false,
				      /*class_head_p=*/false,
				      declarator_p);
	    if (cp_parser_parse_definitely (parser))
	      done = true;
	  }
	/* Look in the surrounding context.  */
	if (!done)
	  {
	    parser->scope = NULL_TREE;
	    parser->object_scope = NULL_TREE;
	    parser->qualifying_scope = NULL_TREE;
	    type_decl
	      = cp_parser_class_name (parser,
				      /*typename_keyword_p=*/false,
				      /*template_keyword_p=*/false,
				      none_type,
				      /*check_dependency=*/false,
				      /*class_head_p=*/false,
				      declarator_p);
	  }
	/* If an error occurred, assume that the name of the
	   destructor is the same as the name of the qualifying
	   class.  That allows us to keep parsing after running
	   into ill-formed destructor names.  */
	if (type_decl == error_mark_node && scope)
	  return build_nt (BIT_NOT_EXPR, scope);
	else if (type_decl == error_mark_node)
	  return error_mark_node;

	/* Check that destructor name and scope match.  */
	if (declarator_p && scope && !check_dtor_name (scope, type_decl))
	  {
	    if (!cp_parser_uncommitted_to_tentative_parse_p (parser))
	      error ("declaration of %<~%T%> as member of %qT",
		     type_decl, scope);
	    cp_parser_simulate_error (parser);
	    return error_mark_node;
	  }

	/* [class.dtor]

	   A typedef-name that names a class shall not be used as the
	   identifier in the declarator for a destructor declaration.  */
	if (declarator_p
	    && !DECL_IMPLICIT_TYPEDEF_P (type_decl)
	    && !DECL_SELF_REFERENCE_P (type_decl)
	    && !cp_parser_uncommitted_to_tentative_parse_p (parser))
	  error ("typedef-name %qD used as destructor declarator",
		 type_decl);

	return build_nt (BIT_NOT_EXPR, TREE_TYPE (type_decl));
      }

    case CPP_KEYWORD:
      if (token->keyword == RID_OPERATOR)
	{
	  tree id;

	  /* This could be a template-id, so we try that first.  */
	  cp_parser_parse_tentatively (parser);
	  /* Try a template-id.  */
	  id = cp_parser_template_id (parser, template_keyword_p,
				      /*check_dependency_p=*/true,
				      declarator_p);
	  /* If that worked, we're done.  */
	  if (cp_parser_parse_definitely (parser))
	    return id;
	  /* We still don't know whether we're looking at an
	     operator-function-id or a conversion-function-id.  */
	  cp_parser_parse_tentatively (parser);
	  /* Try an operator-function-id.  */
	  id = cp_parser_operator_function_id (parser);
	  /* If that didn't work, try a conversion-function-id.  */
	  if (!cp_parser_parse_definitely (parser))
	    id = cp_parser_conversion_function_id (parser);

	  return id;
	}
      /* Fall through.  */

    default:
      if (optional_p)
	return NULL_TREE;
      cp_parser_error (parser, "expected unqualified-id");
      return error_mark_node;
    }
}