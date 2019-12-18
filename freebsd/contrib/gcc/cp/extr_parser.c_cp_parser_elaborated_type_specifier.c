#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  tag_scope ;
typedef  enum tag_types { ____Placeholder_tag_types } tag_types ;
struct TYPE_20__ {scalar_t__ scope; int /*<<< orphan*/  lexer; scalar_t__ num_template_parameter_lists; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 scalar_t__ ATTR_FLAG_TYPE_IN_PLACE ; 
 scalar_t__ CLASSTYPE_TEMPLATE_INSTANTIATION (scalar_t__) ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ DECL_SELF_REFERENCE_P (scalar_t__) ; 
 scalar_t__ NAMESPACE_DECL ; 
 void* NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wattributes ; 
 int /*<<< orphan*/  RID_ENUM ; 
 int /*<<< orphan*/  RID_TYPENAME ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPENAME_TYPE ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ check_elaborated_type_specifier (int,scalar_t__,int) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_attributes_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_check_class_key (int,scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_check_for_invalid_template_id (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_check_template_parameters (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int cp_parser_class_key (TYPE_1__*) ; 
 scalar_t__ cp_parser_declares_only_class_p (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_diagnose_invalid_type_name (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_global_scope_opt (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_identifier (TYPE_1__*) ; 
 scalar_t__ cp_parser_lookup_name (TYPE_1__*,scalar_t__,int,int,int,int,scalar_t__*) ; 
 scalar_t__ cp_parser_make_typename_type (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ cp_parser_maybe_treat_template_as_class (scalar_t__,int) ; 
 int /*<<< orphan*/  cp_parser_nested_name_specifier (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_nested_name_specifier_opt (TYPE_1__*,int,int,int,int) ; 
 scalar_t__ cp_parser_next_token_starts_class_definition_p (TYPE_1__*) ; 
 int cp_parser_optional_template_keyword (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 scalar_t__ cp_parser_template_id (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  cplus_decl_attributes (scalar_t__*,scalar_t__,int) ; 
 int enum_type ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ make_typename_type (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int none_type ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  processing_explicit_instantiation ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  tf_error ; 
 int /*<<< orphan*/  ts_current ; 
 int /*<<< orphan*/  ts_global ; 
 int /*<<< orphan*/  ts_within_enclosing_non_class ; 
 int typename_type ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xref_tag (int,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
cp_parser_elaborated_type_specifier (cp_parser* parser,
				     bool is_friend,
				     bool is_declaration)
{
  enum tag_types tag_type;
  tree identifier;
  tree type = NULL_TREE;
  tree attributes = NULL_TREE;

  /* See if we're looking at the `enum' keyword.  */
  if (cp_lexer_next_token_is_keyword (parser->lexer, RID_ENUM))
    {
      /* Consume the `enum' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Remember that it's an enumeration type.  */
      tag_type = enum_type;
      /* Parse the attributes.  */
      attributes = cp_parser_attributes_opt (parser);
    }
  /* Or, it might be `typename'.  */
  else if (cp_lexer_next_token_is_keyword (parser->lexer,
					   RID_TYPENAME))
    {
      /* Consume the `typename' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Remember that it's a `typename' type.  */
      tag_type = typename_type;
      /* The `typename' keyword is only allowed in templates.  */
      if (!processing_template_decl)
	pedwarn ("using %<typename%> outside of template");
    }
  /* Otherwise it must be a class-key.  */
  else
    {
      tag_type = cp_parser_class_key (parser);
      if (tag_type == none_type)
	return error_mark_node;
      /* Parse the attributes.  */
      attributes = cp_parser_attributes_opt (parser);
    }

  /* Look for the `::' operator.  */
  cp_parser_global_scope_opt (parser,
			      /*current_scope_valid_p=*/false);
  /* Look for the nested-name-specifier.  */
  if (tag_type == typename_type)
    {
      if (!cp_parser_nested_name_specifier (parser,
					   /*typename_keyword_p=*/true,
					   /*check_dependency_p=*/true,
					   /*type_p=*/true,
					    is_declaration))
	return error_mark_node;
    }
  else
    /* Even though `typename' is not present, the proposed resolution
       to Core Issue 180 says that in `class A<T>::B', `B' should be
       considered a type-name, even if `A<T>' is dependent.  */
    cp_parser_nested_name_specifier_opt (parser,
					 /*typename_keyword_p=*/true,
					 /*check_dependency_p=*/true,
					 /*type_p=*/true,
					 is_declaration);
  /* For everything but enumeration types, consider a template-id.
     For an enumeration type, consider only a plain identifier.  */
  if (tag_type != enum_type)
    {
      bool template_p = false;
      tree decl;

      /* Allow the `template' keyword.  */
      template_p = cp_parser_optional_template_keyword (parser);
      /* If we didn't see `template', we don't know if there's a
	 template-id or not.  */
      if (!template_p)
	cp_parser_parse_tentatively (parser);
      /* Parse the template-id.  */
      decl = cp_parser_template_id (parser, template_p,
				    /*check_dependency_p=*/true,
				    is_declaration);
      /* If we didn't find a template-id, look for an ordinary
	 identifier.  */
      if (!template_p && !cp_parser_parse_definitely (parser))
	;
      /* If DECL is a TEMPLATE_ID_EXPR, and the `typename' keyword is
	 in effect, then we must assume that, upon instantiation, the
	 template will correspond to a class.  */
      else if (TREE_CODE (decl) == TEMPLATE_ID_EXPR
	       && tag_type == typename_type)
	type = make_typename_type (parser->scope, decl,
				   typename_type,
				   /*complain=*/tf_error);
      else
	type = TREE_TYPE (decl);
    }

  if (!type)
    {
      identifier = cp_parser_identifier (parser);

      if (identifier == error_mark_node)
	{
	  parser->scope = NULL_TREE;
	  return error_mark_node;
	}

      /* For a `typename', we needn't call xref_tag.  */
      if (tag_type == typename_type
	  && TREE_CODE (parser->scope) != NAMESPACE_DECL)
	return cp_parser_make_typename_type (parser, parser->scope,
					     identifier);
      /* Look up a qualified name in the usual way.  */
      if (parser->scope)
	{
	  tree decl;
	  tree ambiguous_decls;

	  decl = cp_parser_lookup_name (parser, identifier,
					tag_type,
					/*is_template=*/false,
					/*is_namespace=*/false,
					/*check_dependency=*/true,
					&ambiguous_decls);

	  /* If the lookup was ambiguous, an error will already have been
	     issued.  */
	  if (ambiguous_decls)
	    return error_mark_node;

	  /* If we are parsing friend declaration, DECL may be a
	     TEMPLATE_DECL tree node here.  However, we need to check
	     whether this TEMPLATE_DECL results in valid code.  Consider
	     the following example:

	       namespace N {
		 template <class T> class C {};
	       }
	       class X {
		 template <class T> friend class N::C; // #1, valid code
	       };
	       template <class T> class Y {
		 friend class N::C;		       // #2, invalid code
	       };

	     For both case #1 and #2, we arrive at a TEMPLATE_DECL after
	     name lookup of `N::C'.  We see that friend declaration must
	     be template for the code to be valid.  Note that
	     processing_template_decl does not work here since it is
	     always 1 for the above two cases.  */

	  decl = (cp_parser_maybe_treat_template_as_class
		  (decl, /*tag_name_p=*/is_friend
			 && parser->num_template_parameter_lists));

	  if (TREE_CODE (decl) != TYPE_DECL)
	    {
	      cp_parser_diagnose_invalid_type_name (parser,
						    parser->scope,
						    identifier);
	      return error_mark_node;
	    }

	  if (TREE_CODE (TREE_TYPE (decl)) != TYPENAME_TYPE)
            {
              bool allow_template = (parser->num_template_parameter_lists
		                      || DECL_SELF_REFERENCE_P (decl));
              type = check_elaborated_type_specifier (tag_type, decl, 
                                                      allow_template);

              if (type == error_mark_node)
                return error_mark_node;
            }

	  type = TREE_TYPE (decl);
	}
      else
	{
	  /* An elaborated-type-specifier sometimes introduces a new type and
	     sometimes names an existing type.  Normally, the rule is that it
	     introduces a new type only if there is not an existing type of
	     the same name already in scope.  For example, given:

	       struct S {};
	       void f() { struct S s; }

	     the `struct S' in the body of `f' is the same `struct S' as in
	     the global scope; the existing definition is used.  However, if
	     there were no global declaration, this would introduce a new
	     local class named `S'.

	     An exception to this rule applies to the following code:

	       namespace N { struct S; }

	     Here, the elaborated-type-specifier names a new type
	     unconditionally; even if there is already an `S' in the
	     containing scope this declaration names a new type.
	     This exception only applies if the elaborated-type-specifier
	     forms the complete declaration:

	       [class.name]

	       A declaration consisting solely of `class-key identifier ;' is
	       either a redeclaration of the name in the current scope or a
	       forward declaration of the identifier as a class name.  It
	       introduces the name into the current scope.

	     We are in this situation precisely when the next token is a `;'.

	     An exception to the exception is that a `friend' declaration does
	     *not* name a new type; i.e., given:

	       struct S { friend struct T; };

	     `T' is not a new type in the scope of `S'.

	     Also, `new struct S' or `sizeof (struct S)' never results in the
	     definition of a new type; a new type can only be declared in a
	     declaration context.  */

	  tag_scope ts;
	  bool template_p;

	  if (is_friend)
	    /* Friends have special name lookup rules.  */
	    ts = ts_within_enclosing_non_class;
	  else if (is_declaration
		   && cp_lexer_next_token_is (parser->lexer,
					      CPP_SEMICOLON))
	    /* This is a `class-key identifier ;' */
	    ts = ts_current;
	  else
	    ts = ts_global;

	  template_p =
	    (parser->num_template_parameter_lists
	     && (cp_parser_next_token_starts_class_definition_p (parser)
		 || cp_lexer_next_token_is (parser->lexer, CPP_SEMICOLON)));
	  /* An unqualified name was used to reference this type, so
	     there were no qualifying templates.  */
	  if (!cp_parser_check_template_parameters (parser,
						    /*num_templates=*/0))
	    return error_mark_node;
	  type = xref_tag (tag_type, identifier, ts, template_p);
	}
    }

  if (type == error_mark_node)
    return error_mark_node;

  /* Allow attributes on forward declarations of classes.  */
  if (attributes)
    {
      if (TREE_CODE (type) == TYPENAME_TYPE)
	warning (OPT_Wattributes,
		 "attributes ignored on uninstantiated type");
      else if (tag_type != enum_type && CLASSTYPE_TEMPLATE_INSTANTIATION (type)
	       && ! processing_explicit_instantiation)
	warning (OPT_Wattributes,
		 "attributes ignored on template instantiation");
      else if (is_declaration && cp_parser_declares_only_class_p (parser))
	cplus_decl_attributes (&type, attributes, (int) ATTR_FLAG_TYPE_IN_PLACE);
      else
	warning (OPT_Wattributes,
		 "attributes ignored on elaborated-type-specifier that is not a forward declaration");
    }

  if (tag_type != enum_type)
    cp_parser_check_class_key (tag_type, type);

  /* A "<" cannot follow an elaborated type specifier.  If that
     happens, the user was probably trying to form a template-id.  */
  cp_parser_check_for_invalid_template_id (parser, type);

  return type;
}