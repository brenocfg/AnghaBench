#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
struct TYPE_11__ {TYPE_1__* context; scalar_t__ object_scope; scalar_t__ qualifying_scope; scalar_t__ scope; } ;
typedef  TYPE_2__ cp_parser ;
typedef  int /*<<< orphan*/  cp_id_kind ;
struct TYPE_10__ {scalar_t__ object_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASELINK_ACCESS_BINFO (scalar_t__) ; 
 scalar_t__ BASELINK_P (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int CPP_DEREF ; 
 int /*<<< orphan*/  CP_ID_KIND_NONE ; 
 int /*<<< orphan*/  CP_ID_KIND_QUALIFIED ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ SCALAR_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 int /*<<< orphan*/  adjust_result_of_qualified_name_lookup (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_qualified_name (scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ build_x_arrow (scalar_t__) ; 
 scalar_t__ complete_type_or_else (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_parser_id_expression (TYPE_2__*,int /*<<< orphan*/ ,int,int*,int,int) ; 
 scalar_t__ cp_parser_non_integral_constant_expression (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_optional_template_keyword (TYPE_2__*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_pseudo_destructor_name (TYPE_2__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ finish_class_member_access_expr (scalar_t__,scalar_t__,int) ; 
 scalar_t__ finish_pseudo_destructor_expr (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 int type_dependent_expression_p (scalar_t__) ; 
 scalar_t__ unknown_type_node ; 

__attribute__((used)) static tree
cp_parser_postfix_dot_deref_expression (cp_parser *parser,
					enum cpp_ttype token_type,
					tree postfix_expression,
					bool for_offsetof, cp_id_kind *idk)
{
  tree name;
  bool dependent_p;
  bool pseudo_destructor_p;
  tree scope = NULL_TREE;

  /* If this is a `->' operator, dereference the pointer.  */
  if (token_type == CPP_DEREF)
    postfix_expression = build_x_arrow (postfix_expression);
  /* Check to see whether or not the expression is type-dependent.  */
  dependent_p = type_dependent_expression_p (postfix_expression);
  /* The identifier following the `->' or `.' is not qualified.  */
  parser->scope = NULL_TREE;
  parser->qualifying_scope = NULL_TREE;
  parser->object_scope = NULL_TREE;
  *idk = CP_ID_KIND_NONE;
  /* Enter the scope corresponding to the type of the object
     given by the POSTFIX_EXPRESSION.  */
  if (!dependent_p && TREE_TYPE (postfix_expression) != NULL_TREE)
    {
      scope = TREE_TYPE (postfix_expression);
      /* According to the standard, no expression should ever have
	 reference type.  Unfortunately, we do not currently match
	 the standard in this respect in that our internal representation
	 of an expression may have reference type even when the standard
	 says it does not.  Therefore, we have to manually obtain the
	 underlying type here.  */
      scope = non_reference (scope);
      /* The type of the POSTFIX_EXPRESSION must be complete.  */
      if (scope == unknown_type_node)
	{
	  error ("%qE does not have class type", postfix_expression);
	  scope = NULL_TREE;
	}
      else
	scope = complete_type_or_else (scope, NULL_TREE);
      /* Let the name lookup machinery know that we are processing a
	 class member access expression.  */
      parser->context->object_type = scope;
      /* If something went wrong, we want to be able to discern that case,
	 as opposed to the case where there was no SCOPE due to the type
	 of expression being dependent.  */
      if (!scope)
	scope = error_mark_node;
      /* If the SCOPE was erroneous, make the various semantic analysis
	 functions exit quickly -- and without issuing additional error
	 messages.  */
      if (scope == error_mark_node)
	postfix_expression = error_mark_node;
    }

  /* Assume this expression is not a pseudo-destructor access.  */
  pseudo_destructor_p = false;

  /* If the SCOPE is a scalar type, then, if this is a valid program,
     we must be looking at a pseudo-destructor-name.  */
  if (scope && SCALAR_TYPE_P (scope))
    {
      tree s;
      tree type;

      cp_parser_parse_tentatively (parser);
      /* Parse the pseudo-destructor-name.  */
      s = NULL_TREE;
      cp_parser_pseudo_destructor_name (parser, &s, &type);
      if (cp_parser_parse_definitely (parser))
	{
	  pseudo_destructor_p = true;
	  postfix_expression
	    = finish_pseudo_destructor_expr (postfix_expression,
					     s, TREE_TYPE (type));
	}
    }

  if (!pseudo_destructor_p)
    {
      /* If the SCOPE is not a scalar type, we are looking at an
	 ordinary class member access expression, rather than a
	 pseudo-destructor-name.  */
      bool template_p;
      /* Parse the id-expression.  */
      name = (cp_parser_id_expression
	      (parser,
	       cp_parser_optional_template_keyword (parser),
	       /*check_dependency_p=*/true,
	       &template_p,
	       /*declarator_p=*/false,
	       /*optional_p=*/false));
      /* In general, build a SCOPE_REF if the member name is qualified.
	 However, if the name was not dependent and has already been
	 resolved; there is no need to build the SCOPE_REF.  For example;

	     struct X { void f(); };
	     template <typename T> void f(T* t) { t->X::f(); }

	 Even though "t" is dependent, "X::f" is not and has been resolved
	 to a BASELINK; there is no need to include scope information.  */

      /* But we do need to remember that there was an explicit scope for
	 virtual function calls.  */
      if (parser->scope)
	*idk = CP_ID_KIND_QUALIFIED;

      /* If the name is a template-id that names a type, we will get a
	 TYPE_DECL here.  That is invalid code.  */
      if (TREE_CODE (name) == TYPE_DECL)
	{
	  error ("invalid use of %qD", name);
	  postfix_expression = error_mark_node;
	}
      else
	{
	  if (name != error_mark_node && !BASELINK_P (name) && parser->scope)
	    {
	      name = build_qualified_name (/*type=*/NULL_TREE,
					   parser->scope,
					   name,
					   template_p);
	      parser->scope = NULL_TREE;
	      parser->qualifying_scope = NULL_TREE;
	      parser->object_scope = NULL_TREE;
	    }
	  if (scope && name && BASELINK_P (name))
	    adjust_result_of_qualified_name_lookup
	      (name, BINFO_TYPE (BASELINK_ACCESS_BINFO (name)), scope);
	  postfix_expression
	    = finish_class_member_access_expr (postfix_expression, name,
					       template_p);
	}
    }

  /* We no longer need to look up names in the scope of the object on
     the left-hand side of the `.' or `->' operator.  */
  parser->context->object_type = NULL_TREE;

  /* Outside of offsetof, these operators may not appear in
     constant-expressions.  */
  if (!for_offsetof
      && (cp_parser_non_integral_constant_expression
	  (parser, token_type == CPP_DEREF ? "'->'" : "`.'")))
    postfix_expression = error_mark_node;

  return postfix_expression;
}