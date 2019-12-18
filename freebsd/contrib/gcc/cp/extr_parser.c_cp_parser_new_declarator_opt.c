#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_7__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
typedef  int /*<<< orphan*/  cp_cv_quals ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_SQUARE ; 
 int INDIRECT_REF ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cp_parser_direct_new_declarator (TYPE_1__*) ; 
 scalar_t__ cp_parser_parse_definitely (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_1__*) ; 
 int cp_parser_ptr_operator (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_pointer_declarator (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_ptrmem_declarator (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_reference_declarator (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cp_declarator *
cp_parser_new_declarator_opt (cp_parser* parser)
{
  enum tree_code code;
  tree type;
  cp_cv_quals cv_quals;

  /* We don't know if there's a ptr-operator next, or not.  */
  cp_parser_parse_tentatively (parser);
  /* Look for a ptr-operator.  */
  code = cp_parser_ptr_operator (parser, &type, &cv_quals);
  /* If that worked, look for more new-declarators.  */
  if (cp_parser_parse_definitely (parser))
    {
      cp_declarator *declarator;

      /* Parse another optional declarator.  */
      declarator = cp_parser_new_declarator_opt (parser);

      /* Create the representation of the declarator.  */
      if (type)
	declarator = make_ptrmem_declarator (cv_quals, type, declarator);
      else if (code == INDIRECT_REF)
	declarator = make_pointer_declarator (cv_quals, declarator);
      else
	declarator = make_reference_declarator (cv_quals, declarator);

      return declarator;
    }

  /* If the next token is a `[', there is a direct-new-declarator.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_OPEN_SQUARE))
    return cp_parser_direct_new_declarator (parser);

  return NULL;
}