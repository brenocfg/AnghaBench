#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_9__ {scalar_t__ scope; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_abort_tentative_parse (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_diagnose_invalid_type_name (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_id_expression (TYPE_1__*,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_block_or_statement (TYPE_1__*) ; 
 scalar_t__ dependent_type_p (scalar_t__) ; 

__attribute__((used)) static bool
cp_parser_parse_and_diagnose_invalid_type_name (cp_parser *parser)
{
  tree id;

  cp_parser_parse_tentatively (parser);
  id = cp_parser_id_expression (parser,
				/*template_keyword_p=*/false,
				/*check_dependency_p=*/true,
				/*template_p=*/NULL,
				/*declarator_p=*/true,
				/*optional_p=*/false);
  /* After the id-expression, there should be a plain identifier,
     otherwise this is not a simple variable declaration. Also, if
     the scope is dependent, we cannot do much.  */
  if (!cp_lexer_next_token_is (parser->lexer, CPP_NAME)
      || (parser->scope && TYPE_P (parser->scope)
	  && dependent_type_p (parser->scope))
      || TREE_CODE (id) == TYPE_DECL)
    {
      cp_parser_abort_tentative_parse (parser);
      return false;
    }
  if (!cp_parser_parse_definitely (parser))
    return false;

  /* Emit a diagnostic for the invalid type.  */
  cp_parser_diagnose_invalid_type_name (parser, parser->scope, id);
  /* Skip to the end of the declaration; there's no point in
     trying to process it.  */
  cp_parser_skip_to_end_of_block_or_statement (parser);
  return true;
}