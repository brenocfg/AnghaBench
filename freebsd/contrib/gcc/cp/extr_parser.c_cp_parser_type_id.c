#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_decl_specifier_seq ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_ABSTRACT ; 
 int /*<<< orphan*/ * cp_parser_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_type_specifier_seq (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ groktypename (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
cp_parser_type_id (cp_parser* parser)
{
  cp_decl_specifier_seq type_specifier_seq;
  cp_declarator *abstract_declarator;

  /* Parse the type-specifier-seq.  */
  cp_parser_type_specifier_seq (parser, /*is_condition=*/false,
				&type_specifier_seq);
  if (type_specifier_seq.type == error_mark_node)
    return error_mark_node;

  /* There might or might not be an abstract declarator.  */
  cp_parser_parse_tentatively (parser);
  /* Look for the declarator.  */
  abstract_declarator
    = cp_parser_declarator (parser, CP_PARSER_DECLARATOR_ABSTRACT, NULL,
			    /*parenthesized_p=*/NULL,
			    /*member_p=*/false);
  /* Check to see if there really was a declarator.  */
  if (!cp_parser_parse_definitely (parser))
    abstract_declarator = NULL;

  return groktypename (&type_specifier_seq, abstract_declarator);
}