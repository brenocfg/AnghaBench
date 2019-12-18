#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_8__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_NAMESPACE ; 
 scalar_t__ cp_lexer_next_token_is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_attributes_opt (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_identifier (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_namespace_body (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_require (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pop_namespace () ; 
 int /*<<< orphan*/  push_namespace_with_attribs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_parser_namespace_definition (cp_parser* parser)
{
  tree identifier, attribs;

  /* Look for the `namespace' keyword.  */
  cp_parser_require_keyword (parser, RID_NAMESPACE, "`namespace'");

  /* Get the name of the namespace.  We do not attempt to distinguish
     between an original-namespace-definition and an
     extension-namespace-definition at this point.  The semantic
     analysis routines are responsible for that.  */
  if (cp_lexer_next_token_is (parser->lexer, CPP_NAME))
    identifier = cp_parser_identifier (parser);
  else
    identifier = NULL_TREE;

  /* Parse any specified attributes.  */
  attribs = cp_parser_attributes_opt (parser);

  /* Look for the `{' to start the namespace.  */
  cp_parser_require (parser, CPP_OPEN_BRACE, "`{'");
  /* Start the namespace.  */
  push_namespace_with_attribs (identifier, attribs);
  /* Parse the body of the namespace.  */
  cp_parser_namespace_body (parser);
  /* Finish the namespace.  */
  pop_namespace ();
  /* Look for the final `}'.  */
  cp_parser_require (parser, CPP_CLOSE_BRACE, "`}'");
}