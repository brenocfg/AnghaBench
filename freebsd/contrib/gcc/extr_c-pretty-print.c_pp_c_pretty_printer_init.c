#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  expression; int /*<<< orphan*/  assignment_expression; int /*<<< orphan*/  conditional_expression; int /*<<< orphan*/  multiplicative_expression; int /*<<< orphan*/  initializer; int /*<<< orphan*/  unary_expression; int /*<<< orphan*/  postfix_expression; int /*<<< orphan*/  primary_expression; int /*<<< orphan*/  id_expression; int /*<<< orphan*/  constant; int /*<<< orphan*/  statement; int /*<<< orphan*/  storage_class_specifier; int /*<<< orphan*/  function_specifier; int /*<<< orphan*/  simple_type_specifier; int /*<<< orphan*/  type_id; int /*<<< orphan*/  parameter_list; int /*<<< orphan*/  ptr_operator; int /*<<< orphan*/  direct_abstract_declarator; int /*<<< orphan*/  abstract_declarator; int /*<<< orphan*/  type_specifier_seq; int /*<<< orphan*/  direct_declarator; int /*<<< orphan*/  declarator; int /*<<< orphan*/  declaration_specifiers; int /*<<< orphan*/  declaration; scalar_t__ offset_list; } ;
typedef  TYPE_1__ c_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  pp_c_abstract_declarator ; 
 int /*<<< orphan*/  pp_c_assignment_expression ; 
 int /*<<< orphan*/  pp_c_conditional_expression ; 
 int /*<<< orphan*/  pp_c_constant ; 
 int /*<<< orphan*/  pp_c_declaration ; 
 int /*<<< orphan*/  pp_c_declaration_specifiers ; 
 int /*<<< orphan*/  pp_c_declarator ; 
 int /*<<< orphan*/  pp_c_direct_abstract_declarator ; 
 int /*<<< orphan*/  pp_c_direct_declarator ; 
 int /*<<< orphan*/  pp_c_expression ; 
 int /*<<< orphan*/  pp_c_function_specifier ; 
 int /*<<< orphan*/  pp_c_id_expression ; 
 int /*<<< orphan*/  pp_c_initializer ; 
 int /*<<< orphan*/  pp_c_multiplicative_expression ; 
 int /*<<< orphan*/  pp_c_parameter_type_list ; 
 int /*<<< orphan*/  pp_c_pointer ; 
 int /*<<< orphan*/  pp_c_postfix_expression ; 
 int /*<<< orphan*/  pp_c_primary_expression ; 
 int /*<<< orphan*/  pp_c_specifier_qualifier_list ; 
 int /*<<< orphan*/  pp_c_statement ; 
 int /*<<< orphan*/  pp_c_storage_class_specifier ; 
 int /*<<< orphan*/  pp_c_type_id ; 
 int /*<<< orphan*/  pp_c_type_specifier ; 
 int /*<<< orphan*/  pp_c_unary_expression ; 

void
pp_c_pretty_printer_init (c_pretty_printer *pp)
{
  pp->offset_list               = 0;

  pp->declaration               = pp_c_declaration;
  pp->declaration_specifiers    = pp_c_declaration_specifiers;
  pp->declarator                = pp_c_declarator;
  pp->direct_declarator         = pp_c_direct_declarator;
  pp->type_specifier_seq        = pp_c_specifier_qualifier_list;
  pp->abstract_declarator       = pp_c_abstract_declarator;
  pp->direct_abstract_declarator = pp_c_direct_abstract_declarator;
  pp->ptr_operator              = pp_c_pointer;
  pp->parameter_list            = pp_c_parameter_type_list;
  pp->type_id                   = pp_c_type_id;
  pp->simple_type_specifier     = pp_c_type_specifier;
  pp->function_specifier        = pp_c_function_specifier;
  pp->storage_class_specifier   = pp_c_storage_class_specifier;

  pp->statement                 = pp_c_statement;

  pp->constant                  = pp_c_constant;
  pp->id_expression             = pp_c_id_expression;
  pp->primary_expression        = pp_c_primary_expression;
  pp->postfix_expression        = pp_c_postfix_expression;
  pp->unary_expression          = pp_c_unary_expression;
  pp->initializer               = pp_c_initializer;
  pp->multiplicative_expression = pp_c_multiplicative_expression;
  pp->conditional_expression    = pp_c_conditional_expression;
  pp->assignment_expression     = pp_c_assignment_expression;
  pp->expression                = pp_c_expression;
}