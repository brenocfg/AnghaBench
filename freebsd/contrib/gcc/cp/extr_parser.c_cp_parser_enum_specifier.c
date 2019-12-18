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
struct TYPE_13__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 scalar_t__ ATTR_FLAG_TYPE_IN_PLACE ; 
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_lexer_next_token_is_not (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (TYPE_1__*) ; 
 scalar_t__ cp_parser_attributes_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_check_type_definition (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_enumerator_list (TYPE_1__*,scalar_t__) ; 
 scalar_t__ cp_parser_identifier (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_block_or_statement (TYPE_1__*) ; 
 int /*<<< orphan*/  cplus_decl_attributes (scalar_t__*,scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_enum (scalar_t__) ; 
 scalar_t__ make_anon_name () ; 
 scalar_t__ start_enum (scalar_t__) ; 

__attribute__((used)) static tree
cp_parser_enum_specifier (cp_parser* parser)
{
  tree identifier;
  tree type;
  tree attributes;

  /* Parse tentatively so that we can back up if we don't find a
     enum-specifier.  */
  cp_parser_parse_tentatively (parser);

  /* Caller guarantees that the current token is 'enum', an identifier
     possibly follows, and the token after that is an opening brace.
     If we don't have an identifier, fabricate an anonymous name for
     the enumeration being defined.  */
  cp_lexer_consume_token (parser->lexer);

  attributes = cp_parser_attributes_opt (parser);

  if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
    identifier = cp_parser_identifier (parser);
  else
    identifier = make_anon_name ();

  /* Look for the `{' but don't consume it yet.  */
  if (!cp_lexer_next_token_is (parser->lexer, CPP_OPEN_BRACE))
    cp_parser_simulate_error (parser);

  if (!cp_parser_parse_definitely (parser))
    return NULL_TREE;

  /* Issue an error message if type-definitions are forbidden here.  */
  if (!cp_parser_check_type_definition (parser))
    type = error_mark_node;
  else
    /* Create the new type.  We do this before consuming the opening
       brace so the enum will be recorded as being on the line of its
       tag (or the 'enum' keyword, if there is no tag).  */
    type = start_enum (identifier);
  
  /* Consume the opening brace.  */
  cp_lexer_consume_token (parser->lexer);

  if (type == error_mark_node)
    {
      cp_parser_skip_to_end_of_block_or_statement (parser);
      return error_mark_node;
    }

  /* If the next token is not '}', then there are some enumerators.  */
  if (cp_lexer_next_token_is_not (parser->lexer, CPP_CLOSE_BRACE))
    cp_parser_enumerator_list (parser, type);

  /* Consume the final '}'.  */
  cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");

  /* Look for trailing attributes to apply to this enumeration, and
     apply them if appropriate.  */
  if (cp_parser_allow_gnu_extensions_p (parser))
    {
      tree trailing_attr = cp_parser_attributes_opt (parser);
      cplus_decl_attributes (&type,
			     trailing_attr,
			     (int) ATTR_FLAG_TYPE_IN_PLACE);
    }

  /* Finish up the enumeration.  */
  finish_enum (type);

  return type;
}