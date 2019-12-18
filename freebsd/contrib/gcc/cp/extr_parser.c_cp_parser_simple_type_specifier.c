#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_23__ {int keyword; } ;
typedef  TYPE_2__ cp_token ;
typedef  int cp_parser_flags ;
struct TYPE_24__ {scalar_t__ scope; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_3__ cp_parser ;
struct TYPE_25__ {int explicit_char_p; int explicit_int_p; int any_specifiers_p; scalar_t__ type; int /*<<< orphan*/ * specs; } ;
typedef  TYPE_4__ cp_decl_specifier_seq ;
struct TYPE_21__ {scalar_t__ value; } ;
struct TYPE_22__ {TYPE_1__ u; } ;

/* Variables and functions */
 int CP_PARSER_FLAGS_NO_USER_DEFINED_TYPES ; 
 int CP_PARSER_FLAGS_OPTIONAL ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ NULL_TREE ; 
#define  RID_BOOL 139 
#define  RID_CHAR 138 
#define  RID_DOUBLE 137 
#define  RID_FLOAT 136 
#define  RID_INT 135 
#define  RID_LONG 134 
#define  RID_SHORT 133 
#define  RID_SIGNED 132 
#define  RID_TYPEOF 131 
#define  RID_UNSIGNED 130 
#define  RID_VOID 129 
#define  RID_WCHAR 128 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_P (scalar_t__) ; 
 scalar_t__ boolean_type_node ; 
 scalar_t__ c_dialect_objc () ; 
 scalar_t__ char_type_node ; 
 TYPE_20__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_2__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_check_for_invalid_template_id (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_3__*,char*) ; 
 scalar_t__ cp_parser_global_scope_opt (TYPE_3__*,int) ; 
 scalar_t__ cp_parser_nested_name_specifier_opt (TYPE_3__*,int,int,int,int) ; 
 scalar_t__ cp_parser_objc_protocol_refs_opt (TYPE_3__*) ; 
 scalar_t__ cp_parser_optional_template_keyword (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_set_decl_spec_type (TYPE_4__*,scalar_t__,int) ; 
 scalar_t__ cp_parser_sizeof_operand (TYPE_3__*,int const) ; 
 scalar_t__ cp_parser_template_id (TYPE_3__*,int,int,int) ; 
 scalar_t__ cp_parser_type_name (TYPE_3__*) ; 
 scalar_t__ double_type_node ; 
 scalar_t__ ds_long ; 
 scalar_t__ ds_short ; 
 scalar_t__ ds_signed ; 
 scalar_t__ ds_unsigned ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ finish_typeof (scalar_t__) ; 
 scalar_t__ float_type_node ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ long_integer_type_node ; 
 int /*<<< orphan*/  maybe_note_name_used_in_class (scalar_t__,scalar_t__) ; 
 scalar_t__ objc_get_protocol_qualified_type (scalar_t__,scalar_t__) ; 
 scalar_t__ objc_is_class_name (scalar_t__) ; 
 scalar_t__ objc_is_id (scalar_t__) ; 
 scalar_t__ short_integer_type_node ; 
 scalar_t__ unsigned_type_node ; 
 scalar_t__ void_type_node ; 
 scalar_t__ wchar_type_node ; 

__attribute__((used)) static tree
cp_parser_simple_type_specifier (cp_parser* parser,
				 cp_decl_specifier_seq *decl_specs,
				 cp_parser_flags flags)
{
  tree type = NULL_TREE;
  cp_token *token;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);

  /* If we're looking at a keyword, things are easy.  */
  switch (token->keyword)
    {
    case RID_CHAR:
      if (decl_specs)
	decl_specs->explicit_char_p = true;
      type = char_type_node;
      break;
    case RID_WCHAR:
      type = wchar_type_node;
      break;
    case RID_BOOL:
      type = boolean_type_node;
      break;
    case RID_SHORT:
      if (decl_specs)
	++decl_specs->specs[(int) ds_short];
      type = short_integer_type_node;
      break;
    case RID_INT:
      if (decl_specs)
	decl_specs->explicit_int_p = true;
      type = integer_type_node;
      break;
    case RID_LONG:
      if (decl_specs)
	++decl_specs->specs[(int) ds_long];
      type = long_integer_type_node;
      break;
    case RID_SIGNED:
      if (decl_specs)
	++decl_specs->specs[(int) ds_signed];
      type = integer_type_node;
      break;
    case RID_UNSIGNED:
      if (decl_specs)
	++decl_specs->specs[(int) ds_unsigned];
      type = unsigned_type_node;
      break;
    case RID_FLOAT:
      type = float_type_node;
      break;
    case RID_DOUBLE:
      type = double_type_node;
      break;
    case RID_VOID:
      type = void_type_node;
      break;

    case RID_TYPEOF:
      /* Consume the `typeof' token.  */
      cp_lexer_consume_token (parser->lexer);
      /* Parse the operand to `typeof'.  */
      type = cp_parser_sizeof_operand (parser, RID_TYPEOF);
      /* If it is not already a TYPE, take its type.  */
      if (!TYPE_P (type))
	type = finish_typeof (type);

      if (decl_specs)
	cp_parser_set_decl_spec_type (decl_specs, type,
				      /*user_defined_p=*/true);

      return type;

    default:
      break;
    }

  /* If the type-specifier was for a built-in type, we're done.  */
  if (type)
    {
      tree id;

      /* Record the type.  */
      if (decl_specs
	  && (token->keyword != RID_SIGNED
	      && token->keyword != RID_UNSIGNED
	      && token->keyword != RID_SHORT
	      && token->keyword != RID_LONG))
	cp_parser_set_decl_spec_type (decl_specs,
				      type,
				      /*user_defined=*/false);
      if (decl_specs)
	decl_specs->any_specifiers_p = true;

      /* Consume the token.  */
      id = cp_lexer_consume_token (parser->lexer)->u.value;

      /* There is no valid C++ program where a non-template type is
	 followed by a "<".  That usually indicates that the user thought
	 that the type was a template.  */
      cp_parser_check_for_invalid_template_id (parser, type);

      return TYPE_NAME (type);
    }

  /* The type-specifier must be a user-defined type.  */
  if (!(flags & CP_PARSER_FLAGS_NO_USER_DEFINED_TYPES))
    {
      bool qualified_p;
      bool global_p;

      /* Don't gobble tokens or issue error messages if this is an
	 optional type-specifier.  */
      if (flags & CP_PARSER_FLAGS_OPTIONAL)
	cp_parser_parse_tentatively (parser);

      /* Look for the optional `::' operator.  */
      global_p
	= (cp_parser_global_scope_opt (parser,
				       /*current_scope_valid_p=*/false)
	   != NULL_TREE);
      /* Look for the nested-name specifier.  */
      qualified_p
	= (cp_parser_nested_name_specifier_opt (parser,
						/*typename_keyword_p=*/false,
						/*check_dependency_p=*/true,
						/*type_p=*/false,
						/*is_declaration=*/false)
	   != NULL_TREE);
      /* If we have seen a nested-name-specifier, and the next token
	 is `template', then we are using the template-id production.  */
      if (parser->scope
	  && cp_parser_optional_template_keyword (parser))
	{
	  /* Look for the template-id.  */
	  type = cp_parser_template_id (parser,
					/*template_keyword_p=*/true,
					/*check_dependency_p=*/true,
					/*is_declaration=*/false);
	  /* If the template-id did not name a type, we are out of
	     luck.  */
	  if (TREE_CODE (type) != TYPE_DECL)
	    {
	      cp_parser_error (parser, "expected template-id for type");
	      type = NULL_TREE;
	    }
	}
      /* Otherwise, look for a type-name.  */
      else
	type = cp_parser_type_name (parser);
      /* Keep track of all name-lookups performed in class scopes.  */
      if (type
	  && !global_p
	  && !qualified_p
	  && TREE_CODE (type) == TYPE_DECL
	  && TREE_CODE (DECL_NAME (type)) == IDENTIFIER_NODE)
	maybe_note_name_used_in_class (DECL_NAME (type), type);
      /* If it didn't work out, we don't have a TYPE.  */
      if ((flags & CP_PARSER_FLAGS_OPTIONAL)
	  && !cp_parser_parse_definitely (parser))
	type = NULL_TREE;
      if (type && decl_specs)
	cp_parser_set_decl_spec_type (decl_specs, type,
				      /*user_defined=*/true);
    }

  /* If we didn't get a type-name, issue an error message.  */
  if (!type && !(flags & CP_PARSER_FLAGS_OPTIONAL))
    {
      cp_parser_error (parser, "expected type-name");
      return error_mark_node;
    }

  /* There is no valid C++ program where a non-template type is
     followed by a "<".  That usually indicates that the user thought
     that the type was a template.  */
  if (type && type != error_mark_node)
    {
      /* As a last-ditch effort, see if TYPE is an Objective-C type.
	 If it is, then the '<'...'>' enclose protocol names rather than
	 template arguments, and so everything is fine.  */
      if (c_dialect_objc ()
	  && (objc_is_id (type) || objc_is_class_name (type)))
	{
	  tree protos = cp_parser_objc_protocol_refs_opt (parser);
	  tree qual_type = objc_get_protocol_qualified_type (type, protos);

	  /* Clobber the "unqualified" type previously entered into
	     DECL_SPECS with the new, improved protocol-qualified version.  */
	  if (decl_specs)
	    decl_specs->type = qual_type;

	  return qual_type;
	}

      cp_parser_check_for_invalid_template_id (parser, TREE_TYPE (type));
    }

  return type;
}