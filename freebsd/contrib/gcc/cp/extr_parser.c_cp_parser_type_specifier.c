#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_20__ {int keyword; } ;
typedef  TYPE_2__ cp_token ;
typedef  int cp_parser_flags ;
struct TYPE_21__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_3__ cp_parser ;
struct TYPE_22__ {int any_specifiers_p; scalar_t__* specs; } ;
typedef  TYPE_4__ cp_decl_specifier_seq ;
typedef  scalar_t__ cp_decl_spec ;
struct TYPE_19__ {scalar_t__ value; } ;
struct TYPE_18__ {TYPE_1__ u; } ;

/* Variables and functions */
 int CP_PARSER_FLAGS_OPTIONAL ; 
 scalar_t__ NULL_TREE ; 
#define  RID_CLASS 136 
#define  RID_COMPLEX 135 
#define  RID_CONST 134 
#define  RID_ENUM 133 
#define  RID_RESTRICT 132 
#define  RID_STRUCT 131 
#define  RID_TYPENAME 130 
#define  RID_UNION 129 
#define  RID_VOLATILE 128 
 TYPE_17__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_2__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_class_specifier (TYPE_3__*) ; 
 scalar_t__ cp_parser_elaborated_type_specifier (TYPE_3__*,int,int) ; 
 scalar_t__ cp_parser_enum_specifier (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_set_decl_spec_type (TYPE_4__*,scalar_t__,int) ; 
 scalar_t__ cp_parser_simple_type_specifier (TYPE_3__*,TYPE_4__*,int) ; 
 scalar_t__ ds_complex ; 
 scalar_t__ ds_const ; 
 scalar_t__ ds_friend ; 
 scalar_t__ ds_last ; 
 scalar_t__ ds_restrict ; 
 scalar_t__ ds_volatile ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static tree
cp_parser_type_specifier (cp_parser* parser,
			  cp_parser_flags flags,
			  cp_decl_specifier_seq *decl_specs,
			  bool is_declaration,
			  int* declares_class_or_enum,
			  bool* is_cv_qualifier)
{
  tree type_spec = NULL_TREE;
  cp_token *token;
  enum rid keyword;
  cp_decl_spec ds = ds_last;

  /* Assume this type-specifier does not declare a new type.  */
  if (declares_class_or_enum)
    *declares_class_or_enum = 0;
  /* And that it does not specify a cv-qualifier.  */
  if (is_cv_qualifier)
    *is_cv_qualifier = false;
  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);

  /* If we're looking at a keyword, we can use that to guide the
     production we choose.  */
  keyword = token->keyword;
  switch (keyword)
    {
    case RID_ENUM:
      /* Look for the enum-specifier.  */
      type_spec = cp_parser_enum_specifier (parser);
      /* If that worked, we're done.  */
      if (type_spec)
	{
	  if (declares_class_or_enum)
	    *declares_class_or_enum = 2;
	  if (decl_specs)
	    cp_parser_set_decl_spec_type (decl_specs,
					  type_spec,
					  /*user_defined_p=*/true);
	  return type_spec;
	}
      else
	goto elaborated_type_specifier;

      /* Any of these indicate either a class-specifier, or an
	 elaborated-type-specifier.  */
    case RID_CLASS:
    case RID_STRUCT:
    case RID_UNION:
      /* Parse tentatively so that we can back up if we don't find a
	 class-specifier.  */
      cp_parser_parse_tentatively (parser);
      /* Look for the class-specifier.  */
      type_spec = cp_parser_class_specifier (parser);
      /* If that worked, we're done.  */
      if (cp_parser_parse_definitely (parser))
	{
	  if (declares_class_or_enum)
	    *declares_class_or_enum = 2;
	  if (decl_specs)
	    cp_parser_set_decl_spec_type (decl_specs,
					  type_spec,
					  /*user_defined_p=*/true);
	  return type_spec;
	}

      /* Fall through.  */
    elaborated_type_specifier:
      /* We're declaring (not defining) a class or enum.  */
      if (declares_class_or_enum)
	*declares_class_or_enum = 1;

      /* Fall through.  */
    case RID_TYPENAME:
      /* Look for an elaborated-type-specifier.  */
      type_spec
	= (cp_parser_elaborated_type_specifier
	   (parser,
	    decl_specs && decl_specs->specs[(int) ds_friend],
	    is_declaration));
      if (decl_specs)
	cp_parser_set_decl_spec_type (decl_specs,
				      type_spec,
				      /*user_defined_p=*/true);
      return type_spec;

    case RID_CONST:
      ds = ds_const;
      if (is_cv_qualifier)
	*is_cv_qualifier = true;
      break;

    case RID_VOLATILE:
      ds = ds_volatile;
      if (is_cv_qualifier)
	*is_cv_qualifier = true;
      break;

    case RID_RESTRICT:
      ds = ds_restrict;
      if (is_cv_qualifier)
	*is_cv_qualifier = true;
      break;

    case RID_COMPLEX:
      /* The `__complex__' keyword is a GNU extension.  */
      ds = ds_complex;
      break;

    default:
      break;
    }

  /* Handle simple keywords.  */
  if (ds != ds_last)
    {
      if (decl_specs)
	{
	  ++decl_specs->specs[(int)ds];
	  decl_specs->any_specifiers_p = true;
	}
      return cp_lexer_consume_token (parser->lexer)->u.value;
    }

  /* If we do not already have a type-specifier, assume we are looking
     at a simple-type-specifier.  */
  type_spec = cp_parser_simple_type_specifier (parser,
					       decl_specs,
					       flags);

  /* If we didn't find a type-specifier, and a type-specifier was not
     optional in this context, issue an error message.  */
  if (!type_spec && !(flags & CP_PARSER_FLAGS_OPTIONAL))
    {
      cp_parser_error (parser, "expected type specifier");
      return error_mark_node;
    }

  return type_spec;
}