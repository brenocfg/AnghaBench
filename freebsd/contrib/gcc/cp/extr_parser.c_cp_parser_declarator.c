#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_24__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
typedef  int /*<<< orphan*/  cp_parser_declarator_kind ;
struct TYPE_25__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_26__ {scalar_t__ attributes; } ;
typedef  TYPE_3__ cp_declarator ;
typedef  int /*<<< orphan*/  cp_cv_quals ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ CPP_XOR ; 
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_EITHER ; 
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_NAMED ; 
 int INDIRECT_REF ; 
 scalar_t__ NULL_TREE ; 
 TYPE_3__* cp_error_declarator ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 int cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (TYPE_2__*) ; 
 scalar_t__ cp_parser_attributes_opt (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_cv_qualifier_or_attribute_seq_opt (TYPE_2__*,scalar_t__*) ; 
 TYPE_3__* cp_parser_direct_declarator (TYPE_2__*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 int cp_parser_ptr_operator (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ flag_blocks ; 
 TYPE_3__* make_block_pointer_declarator (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* make_pointer_declarator (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* make_ptrmem_declarator (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*) ; 
 TYPE_3__* make_reference_declarator (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static cp_declarator *
cp_parser_declarator (cp_parser* parser,
		      cp_parser_declarator_kind dcl_kind,
		      int* ctor_dtor_or_conv_p,
		      bool* parenthesized_p,
		      bool member_p)
{
  cp_token *token;
  cp_declarator *declarator;
  enum tree_code code;
  cp_cv_quals cv_quals;
  tree class_type;
  tree attributes = NULL_TREE;

  /* Assume this is not a constructor, destructor, or type-conversion
     operator.  */
  if (ctor_dtor_or_conv_p)
    *ctor_dtor_or_conv_p = 0;

  if (cp_parser_allow_gnu_extensions_p (parser))
    attributes = cp_parser_attributes_opt (parser);

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);

  /* APPLE LOCAL begin blocks 6040305 (cc) */
  if (flag_blocks && token->type == CPP_XOR)
    {
      cp_cv_quals quals;
      cp_declarator *inner;
      tree attrs;

      cp_lexer_consume_token (parser->lexer);

      /* cp_parse_declspecs (parser, quals_attrs, false, false, true); */
      quals = cp_parser_cv_qualifier_or_attribute_seq_opt (parser, &attrs);

      inner = cp_parser_declarator (parser, CP_PARSER_DECLARATOR_EITHER, 
				    /*ctor_dtor_or_conv_p=*/NULL,
				    /*parenthesized_p=*/NULL,
				    /*member_p=*/false);
      if (inner == cp_error_declarator)
	return inner;
      return make_block_pointer_declarator (attrs, quals, inner);
    }
  /* APPLE LOCAL end blocks 6040305 (cc) */

  /* Check for the ptr-operator production.  */
  cp_parser_parse_tentatively (parser);
  /* Parse the ptr-operator.  */
  code = cp_parser_ptr_operator (parser,
				 &class_type,
				 &cv_quals);
  /* If that worked, then we have a ptr-operator.  */
  if (cp_parser_parse_definitely (parser))
    {
      /* If a ptr-operator was found, then this declarator was not
	 parenthesized.  */
      if (parenthesized_p)
	*parenthesized_p = true;
      /* The dependent declarator is optional if we are parsing an
	 abstract-declarator.  */
      if (dcl_kind != CP_PARSER_DECLARATOR_NAMED)
	cp_parser_parse_tentatively (parser);

      /* Parse the dependent declarator.  */
      declarator = cp_parser_declarator (parser, dcl_kind,
					 /*ctor_dtor_or_conv_p=*/NULL,
					 /*parenthesized_p=*/NULL,
					 /*member_p=*/false);

      /* If we are parsing an abstract-declarator, we must handle the
	 case where the dependent declarator is absent.  */
      if (dcl_kind != CP_PARSER_DECLARATOR_NAMED
	  && !cp_parser_parse_definitely (parser))
	declarator = NULL;

      /* Build the representation of the ptr-operator.  */
      if (class_type)
	declarator = make_ptrmem_declarator (cv_quals,
					     class_type,
					     declarator);
      else if (code == INDIRECT_REF)
	declarator = make_pointer_declarator (cv_quals, declarator);
      else
	declarator = make_reference_declarator (cv_quals, declarator);
    }
  /* Everything else is a direct-declarator.  */
  else
    {
      if (parenthesized_p)
	*parenthesized_p = cp_lexer_next_token_is (parser->lexer,
						   CPP_OPEN_PAREN);
      declarator = cp_parser_direct_declarator (parser, dcl_kind,
						ctor_dtor_or_conv_p,
						member_p);
    }

  if (attributes && declarator && declarator != cp_error_declarator)
    declarator->attributes = attributes;

  return declarator;
}