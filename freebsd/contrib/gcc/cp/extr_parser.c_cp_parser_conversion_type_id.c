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
 int /*<<< orphan*/  TYPENAME ; 
 scalar_t__ cp_parser_attributes_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cp_parser_conversion_declarator_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_type_specifier_seq (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  cplus_decl_attributes (scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ grokdeclarator (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static tree
cp_parser_conversion_type_id (cp_parser* parser)
{
  tree attributes;
  cp_decl_specifier_seq type_specifiers;
  cp_declarator *declarator;
  tree type_specified;

  /* Parse the attributes.  */
  attributes = cp_parser_attributes_opt (parser);
  /* Parse the type-specifiers.  */
  cp_parser_type_specifier_seq (parser, /*is_condition=*/false,
				&type_specifiers);
  /* If that didn't work, stop.  */
  if (type_specifiers.type == error_mark_node)
    return error_mark_node;
  /* Parse the conversion-declarator.  */
  declarator = cp_parser_conversion_declarator_opt (parser);

  type_specified =  grokdeclarator (declarator, &type_specifiers, TYPENAME,
				    /*initialized=*/0, &attributes);
  if (attributes)
    cplus_decl_attributes (&type_specified, attributes, /*flags=*/0);
  return type_specified;
}