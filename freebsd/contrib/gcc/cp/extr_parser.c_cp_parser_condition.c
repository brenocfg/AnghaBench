#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_14__ {char* type_definition_forbidden_message; } ;
typedef  TYPE_1__ cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_decl_specifier_seq ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_EQ ; 
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_NAMED ; 
 int /*<<< orphan*/  LOOKUP_ONLYCONVERTING ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ convert_from_reference (scalar_t__) ; 
 int /*<<< orphan*/  cp_finish_decl (scalar_t__,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_abort_tentative_parse (TYPE_1__*) ; 
 scalar_t__ cp_parser_asm_specification_opt (TYPE_1__*) ; 
 scalar_t__ cp_parser_attributes_opt (TYPE_1__*) ; 
 scalar_t__ cp_parser_constant_expression (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/ * cp_parser_declarator (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cp_parser_error_occurred (TYPE_1__*) ; 
 scalar_t__ cp_parser_expression (TYPE_1__*,int) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_type_specifier_seq (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fold_non_dependent_expr (scalar_t__) ; 
 int /*<<< orphan*/  pop_scope (scalar_t__) ; 
 scalar_t__ start_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static tree
cp_parser_condition (cp_parser* parser)
{
  cp_decl_specifier_seq type_specifiers;
  const char *saved_message;

  /* Try the declaration first.  */
  cp_parser_parse_tentatively (parser);
  /* New types are not allowed in the type-specifier-seq for a
     condition.  */
  saved_message = parser->type_definition_forbidden_message;
  parser->type_definition_forbidden_message
    = "types may not be defined in conditions";
  /* Parse the type-specifier-seq.  */
  cp_parser_type_specifier_seq (parser, /*is_condition==*/true,
				&type_specifiers);
  /* Restore the saved message.  */
  parser->type_definition_forbidden_message = saved_message;
  /* If all is well, we might be looking at a declaration.  */
  if (!cp_parser_error_occurred (parser))
    {
      tree decl;
      tree asm_specification;
      tree attributes;
      cp_declarator *declarator;
      tree initializer = NULL_TREE;

      /* Parse the declarator.  */
      declarator = cp_parser_declarator (parser, CP_PARSER_DECLARATOR_NAMED,
					 /*ctor_dtor_or_conv_p=*/NULL,
					 /*parenthesized_p=*/NULL,
					 /*member_p=*/false);
      /* Parse the attributes.  */
      attributes = cp_parser_attributes_opt (parser);
      /* Parse the asm-specification.  */
      asm_specification = cp_parser_asm_specification_opt (parser);
      /* If the next token is not an `=', then we might still be
	 looking at an expression.  For example:

	   if (A(a).x)

	 looks like a decl-specifier-seq and a declarator -- but then
	 there is no `=', so this is an expression.  */
      cp_parser_require (parser, CPP_EQ, "`='");
      /* If we did see an `=', then we are looking at a declaration
	 for sure.  */
      if (cp_parser_parse_definitely (parser))
	{
	  tree pushed_scope;
	  bool non_constant_p;

	  /* Create the declaration.  */
	  decl = start_decl (declarator, &type_specifiers,
			     /*initialized_p=*/true,
			     attributes, /*prefix_attributes=*/NULL_TREE,
			     &pushed_scope);
	  /* Parse the assignment-expression.  */
	  initializer
	    = cp_parser_constant_expression (parser,
					     /*allow_non_constant_p=*/true,
					     &non_constant_p);
	  if (!non_constant_p)
	    initializer = fold_non_dependent_expr (initializer);

	  /* Process the initializer.  */
	  cp_finish_decl (decl,
			  initializer, !non_constant_p,
			  asm_specification,
			  LOOKUP_ONLYCONVERTING);

	  if (pushed_scope)
	    pop_scope (pushed_scope);

	  return convert_from_reference (decl);
	}
    }
  /* If we didn't even get past the declarator successfully, we are
     definitely not looking at a declaration.  */
  else
    cp_parser_abort_tentative_parse (parser);

  /* Otherwise, we are looking at an expression.  */
  return cp_parser_expression (parser, /*cast_p=*/false);
}