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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_17__ {scalar_t__ type; scalar_t__ keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_18__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
typedef  int /*<<< orphan*/  cp_id_kind ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ CPP_AND ; 
 scalar_t__ CPP_NAME ; 
 scalar_t__ CPP_NESTED_NAME_SPECIFIER ; 
 scalar_t__ CPP_RSHIFT ; 
 scalar_t__ CPP_SCOPE ; 
 scalar_t__ CPP_TEMPLATE_ID ; 
 int /*<<< orphan*/  DECL_EXTERNAL_LINKAGE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ OFFSET_REF ; 
 int /*<<< orphan*/  REFERENCE_REF_P (int /*<<< orphan*/ ) ; 
 scalar_t__ RID_OPERATOR ; 
 scalar_t__ SCOPE_REF ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TEMPLATE_PARM_INDEX ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ UNBOUND_CLASS_TEMPLATE ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  build_x_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int cp_lexer_next_token_is (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_abort_tentative_parse (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_constant_expression (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 scalar_t__ cp_parser_error_occurred (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_id_expression (TYPE_2__*,int,int,int*,int,int) ; 
 int /*<<< orphan*/  cp_parser_lookup_name (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_next_token_ends_template_argument_p (TYPE_2__*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_primary_expression (TYPE_2__*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_type_id (TYPE_2__*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  fold_non_dependent_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ is_overloaded_fn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  none_type ; 

__attribute__((used)) static tree
cp_parser_template_argument (cp_parser* parser)
{
  tree argument;
  bool template_p;
  bool address_p;
  bool maybe_type_id = false;
  cp_token *token;
  cp_id_kind idk;

  /* There's really no way to know what we're looking at, so we just
     try each alternative in order.

       [temp.arg]

       In a template-argument, an ambiguity between a type-id and an
       expression is resolved to a type-id, regardless of the form of
       the corresponding template-parameter.

     Therefore, we try a type-id first.  */
  cp_parser_parse_tentatively (parser);
  argument = cp_parser_type_id (parser);
  /* If there was no error parsing the type-id but the next token is a '>>',
     we probably found a typo for '> >'. But there are type-id which are
     also valid expressions. For instance:

     struct X { int operator >> (int); };
     template <int V> struct Foo {};
     Foo<X () >> 5> r;

     Here 'X()' is a valid type-id of a function type, but the user just
     wanted to write the expression "X() >> 5". Thus, we remember that we
     found a valid type-id, but we still try to parse the argument as an
     expression to see what happens.  */
  if (!cp_parser_error_occurred (parser)
      && cp_lexer_next_token_is (parser->lexer, CPP_RSHIFT))
    {
      maybe_type_id = true;
      cp_parser_abort_tentative_parse (parser);
    }
  else
    {
      /* If the next token isn't a `,' or a `>', then this argument wasn't
      really finished. This means that the argument is not a valid
      type-id.  */
      if (!cp_parser_next_token_ends_template_argument_p (parser))
	cp_parser_error (parser, "expected template-argument");
      /* If that worked, we're done.  */
      if (cp_parser_parse_definitely (parser))
	return argument;
    }
  /* We're still not sure what the argument will be.  */
  cp_parser_parse_tentatively (parser);
  /* Try a template.  */
  argument = cp_parser_id_expression (parser,
				      /*template_keyword_p=*/false,
				      /*check_dependency_p=*/true,
				      &template_p,
				      /*declarator_p=*/false,
				      /*optional_p=*/false);
  /* If the next token isn't a `,' or a `>', then this argument wasn't
     really finished.  */
  if (!cp_parser_next_token_ends_template_argument_p (parser))
    cp_parser_error (parser, "expected template-argument");
  if (!cp_parser_error_occurred (parser))
    {
      /* Figure out what is being referred to.  If the id-expression
	 was for a class template specialization, then we will have a
	 TYPE_DECL at this point.  There is no need to do name lookup
	 at this point in that case.  */
      if (TREE_CODE (argument) != TYPE_DECL)
	argument = cp_parser_lookup_name (parser, argument,
					  none_type,
					  /*is_template=*/template_p,
					  /*is_namespace=*/false,
					  /*check_dependency=*/true,
					  /*ambiguous_decls=*/NULL);
      if (TREE_CODE (argument) != TEMPLATE_DECL
	  && TREE_CODE (argument) != UNBOUND_CLASS_TEMPLATE)
	cp_parser_error (parser, "expected template-name");
    }
  if (cp_parser_parse_definitely (parser))
    return argument;
  /* It must be a non-type argument.  There permitted cases are given
     in [temp.arg.nontype]:

     -- an integral constant-expression of integral or enumeration
	type; or

     -- the name of a non-type template-parameter; or

     -- the name of an object or function with external linkage...

     -- the address of an object or function with external linkage...

     -- a pointer to member...  */
  /* Look for a non-type template parameter.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
    {
      cp_parser_parse_tentatively (parser);
      argument = cp_parser_primary_expression (parser,
					       /*adress_p=*/false,
					       /*cast_p=*/false,
					       /*template_arg_p=*/true,
					       &idk);
      if (TREE_CODE (argument) != TEMPLATE_PARM_INDEX
	  || !cp_parser_next_token_ends_template_argument_p (parser))
	cp_parser_simulate_error (parser);
      if (cp_parser_parse_definitely (parser))
	return argument;
    }

  /* If the next token is "&", the argument must be the address of an
     object or function with external linkage.  */
  address_p = cp_lexer_next_token_is (parser->lexer, CPP_AND);
  if (address_p)
    cp_lexer_consume_token (parser->lexer);
  /* See if we might have an id-expression.  */
  token = cp_lexer_peek_token (parser->lexer);
  if (token->type == CPP_NAME
      || token->keyword == RID_OPERATOR
      || token->type == CPP_SCOPE
      || token->type == CPP_TEMPLATE_ID
      || token->type == CPP_NESTED_NAME_SPECIFIER)
    {
      cp_parser_parse_tentatively (parser);
      argument = cp_parser_primary_expression (parser,
					       address_p,
					       /*cast_p=*/false,
					       /*template_arg_p=*/true,
					       &idk);
      if (cp_parser_error_occurred (parser)
	  || !cp_parser_next_token_ends_template_argument_p (parser))
	cp_parser_abort_tentative_parse (parser);
      else
	{
	  if (TREE_CODE (argument) == INDIRECT_REF)
	    {
	      gcc_assert (REFERENCE_REF_P (argument));
	      argument = TREE_OPERAND (argument, 0);
	    }

	  if (TREE_CODE (argument) == VAR_DECL)
	    {
	      /* A variable without external linkage might still be a
		 valid constant-expression, so no error is issued here
		 if the external-linkage check fails.  */
	      if (!address_p && !DECL_EXTERNAL_LINKAGE_P (argument))
		cp_parser_simulate_error (parser);
	    }
	  else if (is_overloaded_fn (argument))
	    /* All overloaded functions are allowed; if the external
	       linkage test does not pass, an error will be issued
	       later.  */
	    ;
	  else if (address_p
		   && (TREE_CODE (argument) == OFFSET_REF
		       || TREE_CODE (argument) == SCOPE_REF))
	    /* A pointer-to-member.  */
	    ;
	  else if (TREE_CODE (argument) == TEMPLATE_PARM_INDEX)
	    ;
	  else
	    cp_parser_simulate_error (parser);

	  if (cp_parser_parse_definitely (parser))
	    {
	      if (address_p)
		argument = build_x_unary_op (ADDR_EXPR, argument);
	      return argument;
	    }
	}
    }
  /* If the argument started with "&", there are no other valid
     alternatives at this point.  */
  if (address_p)
    {
      cp_parser_error (parser, "invalid non-type template argument");
      return error_mark_node;
    }

  /* If the argument wasn't successfully parsed as a type-id followed
     by '>>', the argument can only be a constant expression now.
     Otherwise, we try parsing the constant-expression tentatively,
     because the argument could really be a type-id.  */
  if (maybe_type_id)
    cp_parser_parse_tentatively (parser);
  argument = cp_parser_constant_expression (parser,
					    /*allow_non_constant_p=*/false,
					    /*non_constant_p=*/NULL);
  argument = fold_non_dependent_expr (argument);
  if (!maybe_type_id)
    return argument;
  if (!cp_parser_next_token_ends_template_argument_p (parser))
    cp_parser_error (parser, "expected template-argument");
  if (cp_parser_parse_definitely (parser))
    return argument;
  /* We did our best to parse the argument as a non type-id, but that
     was the only alternative that matched (albeit with a '>' after
     it). We can assume it's just a typo from the user, and a
     diagnostic will then be issued.  */
  return cp_parser_type_id (parser);
}